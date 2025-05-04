{
  description = "C/C++ environment with Raylib";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils, ... }@inputs:
    utils.lib.eachDefaultSystem (
      system:
      let
        p = import nixpkgs { inherit system; };
        llvm = p.llvmPackages_latest;

        # Raylib package itself
        raylibPkg = p.raylib;

        # Build inputs needed for Raylib (especially on non-NixOS)
        # These are often needed for linking graphics, audio, etc.
        raylibBuildInputs = with p; [
          # Add libraries typically required by raylib
          xorg.libX11
          xorg.libXrandr
          xorg.libXinerama
          xorg.libXcursor
          xorg.libXi
          alsa-lib # For audio
          mesa     # For OpenGL
          libGL    # For OpenGL
        ];

        # Updated mk script to link Raylib
        # Arguments: outfile [optional flags]
        # Basic usage example: mk main_program
        # Example with flags: mk main_program -O2
        mymake = p.writeShellScriptBin "mk" ''
          #!${p.stdenv.shell}
          set -e # Exit on error

          if [ -z "$1" ]; then
            echo "Usage: mk <output_filename_without_extension> [compiler_flags...]"
            exit 1
          fi

          input_base=$1
          output_file=$1
          compiler=""
          source_file=""

          # Determine if it's C or C++
          source_file="$input_base.c"
          compiler=$CC
          # Common C flags + Raylib flags
          # Using pkg-config is more robust if available and configured
          # flags="-ggdb -Wall -lm $(pkg-config --cflags --libs raylib) $@"
          # Manual flags as a fallback or simpler alternative:
          flags="-ggdb -Wall -lm -lraylib -lpthread -ldl -lrt -lX11 $@" # Added Raylib and common dependencies

          shift # Remove the output filename from arguments

          echo "Compiling $source_file -> $output_file with flags: $flags"
          # The $@ includes any additional flags passed to mk script
          $compiler $flags ./$source_file -o $output_file

          echo "Compilation successful: $output_file"
        '';
      in
      {
        devShell = p.mkShell.override { stdenv = p.clangStdenv; } rec {
          packages = with p; [
            # Raylib itself
            raylibPkg

            # Build inputs that might be needed by Raylib at runtime or link time
            # Adding them here makes them available in the shell environment
          ] ++ raylibBuildInputs ++ (with p; [
            # builder
            gnumake
            ninja

            # debugger
            llvm.lldb
            gdb

            # fix headers not found / language server
            clang-tools
            llvm.clang # Provides clangd

            # LSP and compiler (Clang is primary via stdenv)
            llvm.libstdcxxClang # C++ standard library for Clang

            # other tools
            cppcheck
            llvm.libllvm
            valgrind
            mymake # Our updated build script

            # stdlib for cpp (already included via llvm.libstdcxxClang)
            # llvm.libcxx # Usually not needed if using libstdcxxClang

            # Tool for discovering library flags (optional but good practice)
            pkg-config
          ]);

          # Environment variables can sometimes help tools find libraries/headers
          # Example (might not be strictly necessary if Nix handles paths well):
          # NIX_CFLAGS_COMPILE = "-I${raylibPkg}/include";
          # NIX_LDFLAGS = "-L${raylibPkg}/lib";

          name = "C-Raylib";
        };
      }
    );
}
