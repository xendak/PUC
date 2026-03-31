const std = @import("std");
const dyn = @import("dynamic_array.zig");

const Arr = dyn.DynArray(u32);

pub const AdjMatrix = struct {
    n: u32,
    m: u32,
    data: []bool,
    allocator: std.mem.Allocator,

    pub fn init(allocator: std.mem.Allocator, n: u32, m: u32) !@This() {
        const sz = @as(usize, n) * @as(usize, m);
        const data = try allocator.alloc(bool, sz);
        @memset(data, false);
        return .{
            .n = n,
            .m = m,
            .allocator = allocator,
            .data = data,
        };
    }

    pub fn deinit(self: @This()) void {
        self.allocator.free(self.data);
    }

    inline fn idx(self: @This(), i: u32, j: u32) usize {
        return @as(usize, i) * @as(usize, self.n) + @as(usize, j);
    }

    pub fn addEdge(self: @This(), src: u32, dst: u32) void {
        self.data[self.idx(src - 1, dst - 1)] = true;
    }

    pub fn outDegree(self: @This(), v: u32) u32 {
        const row = v - 1;
        var deg: u32 = 0;
        var col: u32 = 0;
        while (col < self.n) : (col += 1) {
            if (self.data[self.idx(row, col)]) deg += 1;
        }
        return deg;
    }

    pub fn inDegree(self: @This(), v: u32) u32 {
        const col = v - 1;
        var row: u32 = 0;
        var deg: u32 = 0;

        while (row < self.n) : (row += 1) {
            if (self.data[self.idx(row, col)]) deg += 1;
        }
        return deg;
    }

    // callee owns the memory to the successor array
    pub fn successors(self: *const @This(), v: u32, allocator: std.mem.Allocator) !Arr {
        var res = try Arr.init(allocator);
        const row = v - 1;
        for (0..self.n) |i| {
            const col: u32 = @truncate(i);
            if (self.data[self.idx(row, col)])
                try res.append(col + 1);
        }
        return res;
    }

    // callee owns the memory to the predecessor array
    pub fn predecessors(self: *const @This(), v: u32, allocator: std.mem.Allocator) !Arr {
        var res = try Arr.init(allocator);
        const col = v - 1;
        for (0..self.n) |i| {
            const row: u32 = @truncate(i);
            if (self.data[self.idx(row, col)])
                try res.append(row + 1);
        }
        return res;
    }
};

test "no edges" {
    const allocator = std.testing.allocator;
    var g = try AdjMatrix.init(allocator, 3, 3);
    defer g.deinit();

    try std.testing.expectEqual(@as(u32, 0), g.outDegree(1));
    try std.testing.expectEqual(@as(u32, 0), g.inDegree(1));
}

test "outDegree" {
    const allocator = std.testing.allocator;
    // 3-node graph: 1->2, 1->3, 2->3
    var g = try AdjMatrix.init(allocator, 3, 3);
    defer g.deinit();

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);

    try std.testing.expectEqual(@as(u32, 2), g.outDegree(1));
    try std.testing.expectEqual(@as(u32, 1), g.outDegree(2));
    try std.testing.expectEqual(@as(u32, 0), g.outDegree(3));
}

test "inDegree" {
    const allocator = std.testing.allocator;
    var g = try AdjMatrix.init(allocator, 3, 3);
    defer g.deinit();

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);

    try std.testing.expectEqual(@as(u32, 0), g.inDegree(1));
    try std.testing.expectEqual(@as(u32, 1), g.inDegree(2));
    try std.testing.expectEqual(@as(u32, 2), g.inDegree(3));
}

test "successors" {
    const allocator = std.testing.allocator;
    var g = try AdjMatrix.init(allocator, 3, 3);
    defer g.deinit();

    g.addEdge(1, 2);
    g.addEdge(1, 3);

    var succ = try g.successors(1, allocator);
    defer succ.deinit();

    std.debug.print("successors of 1: ", .{});
    for (succ.items()) |v| std.debug.print("{d} ", .{v});
    std.debug.print("\n", .{});

    try std.testing.expectEqual(@as(usize, 2), succ.len);
    try std.testing.expectEqual(@as(u32, 2), succ.items()[0]);
    try std.testing.expectEqual(@as(u32, 3), succ.items()[1]);
}

test "predecessors" {
    const allocator = std.testing.allocator;
    var g = try AdjMatrix.init(allocator, 3, 3);
    defer g.deinit();

    g.addEdge(1, 3);
    g.addEdge(2, 3);

    var pred = try g.predecessors(3, allocator);
    defer pred.deinit();

    std.debug.print("predecessors of 3: ", .{});
    for (pred.items()) |v| std.debug.print("{d} ", .{v});
    std.debug.print("\n", .{});

    try std.testing.expectEqual(@as(usize, 2), pred.len);
    try std.testing.expectEqual(@as(u32, 1), pred.items()[0]);
    try std.testing.expectEqual(@as(u32, 2), pred.items()[1]);
}

test "from ex slide" {
    const allocator = std.testing.allocator;
    var g = try AdjMatrix.init(allocator, 5, 5);
    defer g.deinit();

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 2);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    try std.testing.expectEqual(g.inDegree(1), 0);
    try std.testing.expectEqual(g.inDegree(2), 2);
    try std.testing.expectEqual(g.inDegree(3), 1);
    try std.testing.expectEqual(g.inDegree(4), 2);
    try std.testing.expectEqual(g.inDegree(5), 2);

    try std.testing.expectEqual(g.outDegree(1), 2);
    try std.testing.expectEqual(g.outDegree(2), 2);
    try std.testing.expectEqual(g.outDegree(3), 2);
    try std.testing.expectEqual(g.outDegree(4), 1);
    try std.testing.expectEqual(g.outDegree(5), 0);

    std.debug.print("Slide Example:\n", .{});
    for (1..6) |i| {
        const idx: u32 = @truncate(i);
        var succ = try g.successors(idx, allocator);
        defer succ.deinit();

        if (succ.len > 0) {
            std.debug.print("successors of {d}: ", .{i});
            for (succ.items()) |v| std.debug.print("{d} ", .{v});
            std.debug.print("\n", .{});
        }

        var pred = try g.predecessors(idx, allocator);
        defer pred.deinit();

        if (pred.len > 0) {
            std.debug.print("predecessors of {d}: ", .{i});
            for (pred.items()) |v| std.debug.print("{d} ", .{v});
            std.debug.print("\n", .{});
        }
    }

    const verification = [_][5]bool{
        .{ false, true, true, false, false },
        .{ false, false, false, true, true },
        .{ false, true, false, true, false },
        .{ false, false, false, false, true },
        .{ false, false, false, false, false },
    };
    const flat: *const [25]bool = @ptrCast(&verification);
    try std.testing.expectEqualSlices(bool, flat, g.data);
}
