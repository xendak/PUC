const std = @import("std");
const raylib_build = @import("raylib");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "rbtree", // The name of the output binary
        .target = target,
        .optimize = optimize,
    });
    exe.addCSourceFile(.{ .file = b.path("rbtree_raylib.c"), .flags = &.{} });

    b.installArtifact(exe);

    //--------------------------------------------------------------------------------------
    const raylib_dep = b.dependency("raylib", .{
        .target = target,
        .optimize = optimize,
        .shared = true,
        .linux_display_backend = .X11,
    });
    const raylib = raylib_dep.artifact("raylib");

    const raygui_dep = b.dependency("raygui", .{});

    raylib_build.addRaygui(b, raylib, raygui_dep, .{ .linux_display_backend = .X11 });

    exe.linkLibrary(raylib);
    b.installArtifact(raylib);
    //--------------------------------------------------------------------------------------

    const run_cmd = b.addRunArtifact(exe);

    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
