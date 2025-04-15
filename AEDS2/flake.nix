{
  description = "Combined Java and C/C++ development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils, ... }:
    let
      javaVersion = 23; # JDK version for Java environment
    in
    {
      overlays.default = final: prev: let
        jdk = prev."jdk${toString javaVersion}";
      in {
        inherit jdk;
        maven = prev.maven.override { jdk_headless = jdk; };
        gradle = prev.gradle.override { java = jdk; };
        lombok = prev.lombok.override { inherit jdk; };
      };
    } // utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [ self.overlays.default ];
        };
        llvm = pkgs.llvmPackages_latest;

        # Custom build script from C++ environment
        mymake = pkgs.writeShellScriptBin "mk" ''
          if [ -f "$1.c" ]; then
            i="$1.c"
            c=$CC
          else
            i="$1.cpp"
            c=$CXX
          fi
          o=$1
          shift
          $c -ggdb $i -o $o -lm -Wall $@
        '';
      in
      {
        devShells.default = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } rec {
          packages = with pkgs; [
            # Java environment
            jdk
            gradle
            maven
            lombok
            gcc
            ncurses
            patchelf
            zlib

            # C/C++ environment
            gnumake
            cmake
            bear
            llvm.lldb
            gdb
            clang-tools
            llvm.libstdcxxClang
            cppcheck
            llvm.libllvm
            valgrind
            mymake
            llvm.libcxx
            glm
            SDL2
            SDL2_gfx
          ];

          shellHook =
            let
              loadLombok = "-javaagent:${pkgs.lombok}/share/java/lombok.jar";
              prev = "\${JAVA_TOOL_OPTIONS:+ $JAVA_TOOL_OPTIONS}";
            in
            ''
              export JAVA_TOOL_OPTIONS="${loadLombok}${prev}"
            '';
        };
      }
    );
}
