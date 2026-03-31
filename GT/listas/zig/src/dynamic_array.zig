const std = @import("std");

const INITIAL_CAPACITY: usize = 8;

pub fn DynArray(comptime T: type) type {
    return struct {
        ptr: [*]T,
        len: usize,
        capacity: usize,
        allocator: std.mem.Allocator,

        const Self = @This();

        pub fn init(allocator: std.mem.Allocator) !Self {
            const slice = try allocator.alloc(T, INITIAL_CAPACITY);
            return .{
                .ptr = slice.ptr,
                .len = 0,
                .capacity = INITIAL_CAPACITY,
                .allocator = allocator,
            };
        }

        pub fn deinit(self: *Self) void {
            const slice: []T = self.ptr[0..self.capacity];
            self.allocator.free(slice);
            self.len = 0;
            self.capacity = 0;
        }

        pub fn append(self: *Self, value: T) !void {
            if (self.capacity <= self.len) {
                try self.grow();
            }
            self.ptr[self.len] = value;
            self.len += 1;
        }

        pub fn grow(self: *Self) !void {
            const new_capacity: usize = self.capacity * 3 / 2;
            const new_slice = try self.allocator.alloc(T, new_capacity);

            @memcpy(new_slice[0..self.len], self.ptr[0..self.len]);

            const old: []T = self.ptr[0..self.capacity];
            self.allocator.free(old);

            self.ptr = new_slice.ptr;
            self.capacity = new_capacity;
        }

        pub fn items(self: *const Self) []const T {
            return self.ptr[0..self.len];
        }

        pub fn shrink(self: *Self) !void {
            if (self.len == self.capacity) return;

            const new = try self.allocator.alloc(T, self.len);

            @memcpy(new[0..self.len], self.ptr[0..self.len]);

            const old: []T = self.ptr[0..self.capacity];
            self.allocator.free(old);

            self.ptr = new.ptr;
            self.capacity = self.len;
        }

        //
        pub fn remove(self: *Self) void {
            _ = self;
            @compileError("TODO: not yet implemented");
        }

        // todo: add fmt options ? how the fk?
    };
}

test "init" {
    var arr = try DynArray(u32).init(std.testing.allocator);
    defer arr.deinit();

    try std.testing.expectEqual(@as(usize, 0), arr.len);
    try std.testing.expectEqual(@as(usize, INITIAL_CAPACITY), arr.capacity);
    try std.testing.expectEqualSlices(u32, &.{}, arr.items());
}

test "append" {
    var arr = try DynArray(u32).init(std.testing.allocator);
    defer arr.deinit();

    for (0..INITIAL_CAPACITY) |i| {
        try arr.append(@as(u32, @intCast(i)));
    }
    try std.testing.expectEqual(INITIAL_CAPACITY, arr.len);
    try std.testing.expectEqual(INITIAL_CAPACITY, arr.capacity);
    for (arr.items(), 0..) |val, i| {
        try std.testing.expectEqual(@as(u32, @intCast(i)), val);
    }
}

test "grow" {
    var arr = try DynArray(u32).init(std.testing.allocator);
    defer arr.deinit();

    // grows twice
    for (0..13) |i| {
        try arr.append(@as(u32, @intCast(i)));
    }
    try std.testing.expectEqual(13, arr.len);
    try std.testing.expectEqual(18, arr.capacity);
    for (arr.items(), 0..) |val, i| {
        try std.testing.expectEqual(@as(u32, @intCast(i)), val);
    }
}

test "shrink" {
    var arr = try DynArray(u32).init(std.testing.allocator);
    defer arr.deinit();

    // grows twice
    for (0..5) |i| {
        try arr.append(@as(u32, @intCast(i)));
    }
    try std.testing.expectEqual(5, arr.len);
    try std.testing.expectEqual(INITIAL_CAPACITY, arr.capacity);
    for (arr.items(), 0..) |val, i| {
        try std.testing.expectEqual(@as(u32, @intCast(i)), val);
    }

    try arr.shrink();

    try std.testing.expectEqual(5, arr.len);
    try std.testing.expectEqual(5, arr.capacity);
    for (arr.items(), 0..) |val, i| {
        try std.testing.expectEqual(@as(u32, @intCast(i)), val);
    }
}
