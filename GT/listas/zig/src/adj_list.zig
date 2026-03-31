const std = @import("std");
const dyn = @import("dynamic_array.zig");

const Arr = dyn.DynArray(u32);

pub fn Node(comptime T: type) type {
    return struct {
        v: T,
        list: dyn.DynArray(T),
    };
}

pub const AdjList = struct {
    node: []Node(u32),
    allocator: std.mem.Allocator,

    pub fn init(allocator: std.mem.Allocator, vertices: u32) !@This() {
        const sz = @as(usize, vertices);
        var node: []Node(u32) = try allocator.alloc(Node(u32), sz);
        for (0..sz) |i| {
            node[i] = .{ .v = @intCast(i + 1), .list = try Arr.init(allocator) };
        }
        return .{
            .node = node,
            .allocator = allocator,
        };
    }

    pub fn deinit(self: @This()) void {
        for (0..self.node.len) |i| {
            self.node[i].list.deinit();
        }
        self.allocator.free(self.node);
    }

    pub fn addEdge(self: @This(), src: u32, dst: u32) !void {
        // TODO: eventually add a value to this
        self.node[src - 1].v = src;
        try self.node[src - 1].list.append(dst);
    }

    pub fn outDegree(self: @This(), v: u32) u32 {
        return @intCast(self.node[v - 1].list.len);
    }

    pub fn inDegree(self: @This(), v: u32) u32 {
        var deg: u32 = 0;
        for (self.node) |n| {
            for (n.list.items()) |val| {
                if (val == v) deg += 1;
            }
        }
        return deg;
    }

    pub fn successors(self: *const @This(), v: u32) Arr {
        return self.node[v - 1].list;
    }

    // callee owns the memory to the predecessor array
    pub fn predecessors(self: *const @This(), v: u32, allocator: std.mem.Allocator) !Arr {
        var res = try Arr.init(allocator);
        for (self.node) |n| {
            for (n.list.items()) |val| {
                if (val == v) try res.append(n.v);
            }
        }
        return res;
    }
};

test "no edges" {
    const allocator = std.testing.allocator;
    var g = try AdjList.init(allocator, 3);
    defer g.deinit();

    try std.testing.expectEqual(@as(u32, 0), g.outDegree(1));
    try std.testing.expectEqual(@as(u32, 0), g.inDegree(1));
}

test "outDegree" {
    const allocator = std.testing.allocator;
    var g = try AdjList.init(allocator, 3);
    defer g.deinit();

    try g.addEdge(1, 2);
    try g.addEdge(1, 3);
    try g.addEdge(2, 3);

    try std.testing.expectEqual(@as(u32, 2), g.outDegree(1));
    try std.testing.expectEqual(@as(u32, 1), g.outDegree(2));
    try std.testing.expectEqual(@as(u32, 0), g.outDegree(3));
}

test "inDegree" {
    const allocator = std.testing.allocator;
    var g = try AdjList.init(allocator, 3);
    defer g.deinit();

    try g.addEdge(1, 2);
    try g.addEdge(1, 3);
    try g.addEdge(2, 3);

    try std.testing.expectEqual(@as(u32, 0), g.inDegree(1));
    try std.testing.expectEqual(@as(u32, 1), g.inDegree(2));
    try std.testing.expectEqual(@as(u32, 2), g.inDegree(3));
}

test "successors" {
    const allocator = std.testing.allocator;
    var g = try AdjList.init(allocator, 3);
    defer g.deinit();

    try g.addEdge(1, 2);
    try g.addEdge(1, 3);

    const succ = g.successors(1);

    try std.testing.expectEqual(@as(usize, 2), succ.len);
    try std.testing.expectEqual(@as(u32, 2), succ.items()[0]);
    try std.testing.expectEqual(@as(u32, 3), succ.items()[1]);
}

test "predecessors" {
    const allocator = std.testing.allocator;
    var g = try AdjList.init(allocator, 3);
    defer g.deinit();

    try g.addEdge(1, 3);
    try g.addEdge(2, 3);

    var pred = try g.predecessors(3, allocator);
    defer pred.deinit();

    try std.testing.expectEqual(@as(usize, 2), pred.len);
    try std.testing.expectEqual(@as(u32, 1), pred.items()[0]);
    try std.testing.expectEqual(@as(u32, 2), pred.items()[1]);
}

test "from ex slide" {
    const allocator = std.testing.allocator;
    var g = try AdjList.init(allocator, 5);
    defer g.deinit();

    try g.addEdge(1, 2);
    try g.addEdge(1, 3);
    try g.addEdge(2, 4);
    try g.addEdge(2, 5);
    try g.addEdge(3, 2);
    try g.addEdge(3, 4);
    try g.addEdge(4, 5);

    try std.testing.expectEqual(@as(u32, 0), g.inDegree(1));
    try std.testing.expectEqual(@as(u32, 2), g.inDegree(2));
    try std.testing.expectEqual(@as(u32, 1), g.inDegree(3));
    try std.testing.expectEqual(@as(u32, 2), g.inDegree(4));
    try std.testing.expectEqual(@as(u32, 2), g.inDegree(5));

    try std.testing.expectEqual(@as(u32, 2), g.outDegree(1));
    try std.testing.expectEqual(@as(u32, 2), g.outDegree(2));
    try std.testing.expectEqual(@as(u32, 2), g.outDegree(3));
    try std.testing.expectEqual(@as(u32, 1), g.outDegree(4));
    try std.testing.expectEqual(@as(u32, 0), g.outDegree(5));

    std.debug.print("Slide Example:\n", .{});
    for (1..6) |i| {
        const v: u32 = @truncate(i);
        const succ = g.successors(v);
        if (succ.len > 0) {
            std.debug.print("successors of {d}: ", .{v});
            for (succ.items()) |s| std.debug.print("{d} ", .{s});
            std.debug.print("\n", .{});
        }
        var pred = try g.predecessors(v, allocator);
        defer pred.deinit();
        if (pred.len > 0) {
            std.debug.print("predecessors of {d}: ", .{v});
            for (pred.items()) |p| std.debug.print("{d} ", .{p});
            std.debug.print("\n", .{});
        }
    }
}
