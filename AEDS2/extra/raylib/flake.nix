{
  description = "C/C++ environment with Raylib for Wayland";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      utils,
      ...
    }@inputs:
    utils.lib.eachDefaultSystem (
      system:
      let
        p = import nixpkgs { inherit system; };
        llvm = p.llvmPackages_latest;

        # 1. Override the raylib package to build with Wayland support.
        raylibPkg = p.raylib;
        # raylibPkg = p.raylib.overrideAttrs (oldAttrs: {
        #   makeFlags = (oldAttrs.makeFlags or [ ]) ++ [ "GLFW_LINUX_ENABLE_WAYLAND=TRUE" ];
        # });
        rayguiPkg = p.raygui;

        # 2. Change build inputs from Xorg to Wayland.
        #    These libraries are needed for linking your program against raylib.
        raylibBuildInputs = with p; [
          # Wayland libraries
          wayland
          wayland-protocols
          libxkbcommon

          xorg.libX11
          xorg.libXrandr
          xorg.libXinerama
          xorg.libXcursor
          xorg.libXi
          # Libraries for audio and OpenGL (still needed)
          alsa-lib
          mesa
          libGL
        ];

        # 3. Update the build script to be generic using pkg-config.
        #    This avoids hardcoding "-lX11" and automatically uses the correct flags.
        mymake = p.writeShellScriptBin "mk" ''
          #!/bin/sh
          set -e

          if [ -z "$1" ]; then
            echo "Usage: mk <output_filename_without_extension> [compiler_flags...]"
            exit 1
          fi

          input_base=$1
          output_file=$1
          source_file="$input_base.c"

          # Use pkg-config to get the correct compile and link flags for raylib.
          # This is more robust than hardcoding flags like -lraylib or -lX11.
          RAYLIB_FLAGS=$(pkg-config --libs --cflags raylib)

          # Additional flags for your project.
          # Note we removed the hardcoded "-lraylib", "-lX11", etc.
          # They are now handled by $RAYLIB_FLAGS.
          OTHER_FLAGS="-ggdb -Wall -lm -lpthread ''${@:2}"

          echo "Compiling $source_file -> $output_file"
          $CC "$source_file" -o "$output_file" $RAYLIB_FLAGS $OTHER_FLAGS
          echo "Compilation successful: $output_file"
        '';
      in
      {
        devShell = p.mkShell.override { stdenv = p.clangStdenv; } rec {
          packages = [
            # Our Wayland-enabled Raylib
            raylibPkg
            rayguiPkg

            # Build/linking dependencies
          ]
          ++ raylibBuildInputs
          ++ (with p; [
            # builder
            gnumake
            ninja

            # waylando
            wayland
            wayland-scanner

            # X11
            xorg.libX11
            xorg.libXrandr
            xorg.libXinerama
            xorg.libXcursor
            xorg.libXi

            # debugger
            llvm.lldb
            gdb

            # language server
            clang-tools
            llvm.clang

            # C++ standard library
            llvm.libstdcxxClang

            # other tools
            cppcheck
            valgrind
            mymake # Our updated build script
            pkg-config # Crucial for our updated script
          ]);

          name = "C-Raylib-Wayland";
        };
      }
    );
}
