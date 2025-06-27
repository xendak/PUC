{
  description = "Combined Java and C/C++ development environment";

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
    }:
    let
      javaVersion = 23; # JDK version for Java environment
    in
    {
      overlays.default =
        final: prev:
        let
          jdk = prev."jdk${toString javaVersion}";
        in
        {
          inherit jdk;
          maven = prev.maven.override { jdk_headless = jdk; };
          gradle = prev.gradle.override { java = jdk; };
          lombok = prev.lombok.override { inherit jdk; };
        };
    }
    // utils.lib.eachDefaultSystem (
      system:
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
        verde_rename_download = pkgs.writeShellScriptBin "vdd" ''
          mv "$PWD/pub.in" "$1.in"
          mv "$PWD/pub.out" "$1.out"
        '';
        verde_download = pkgs.writeShellScriptBin "vd" ''
          curl "http://verde.icei.pucminas.br:3333/atividade/zip/$1" \
            -H 'User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:139.0) Gecko/20100101 Firefox/139.0' \
            -H 'Accept: */*' \
            -H 'Accept-Language: en-US,en;q=0.5' \
            -H 'Accept-Encoding: gzip, deflate' \
            -H "Authorization: Bearer $2" \
            -H 'Referer: http://verde.icei.pucminas.br/' \
            -H 'Origin: http://verde.icei.pucminas.br' \
            -H 'Connection: keep-alive' \
            --output "$PWD/pubs.zip"

            unzip "$PWD/pubs.zip"
            rm "$PWD/pubs.zip"
        '';
        verde_run = pkgs.writeShellScriptBin "vr" ''
          set -e

          # Cleanup function
          cleanup() {
            if [ -n "$binary_to_cleanup" ] && [ -f "$binary_to_cleanup" ]; then
              rm -f "$binary_to_cleanup"
            fi
          }

          # Set trap to cleanup on script exit (normal exit, interrupt, termination)
          trap cleanup EXIT INT TERM

          # Check if program name is provided
          if [ $# -eq 0 ]; then
            echo "Usage: vr <program> [expected_output_file]"
            echo "Examples:"
            echo "  vr program"
            echo "  vr program /path/to/expected_output.file"
            exit 1
          fi

          program_name="$1"
          expected_output="$2"

          get_files_diff() {
            local file1=$1
            local file2=$2

            local lines_arq1=$(wc -l < "$file1")
            local lines_arq2=$(wc -l < "$file2")
            local diff_lines=$(git diff --ignore-cr-at-eol --no-index --stat "$file1" "$file2" 2>/dev/null | tail -1 | awk '{print $4}' || echo "")
            if [ -z "$diff_lines" ]; then
              echo -e "$(tput setaf 3)$(tput bold)Percentual: 100%$(tput sgr0)"
            else
              local diff_perc=$(awk "BEGIN { printf \"%.2f\", ($diff_lines / ($lines_arq1 + $lines_arq2)) * 100 }")
              local equal_perc=$(awk "BEGIN { printf \"%.2f\", 100 - $diff_perc }")
              echo -e "$(tput setaf 3)$(tput bold)Percentual: $equal_perc%$(tput sgr0)"
            fi
            
            if command -v difft >/dev/null 2>&1; then
              echo "$(tput setaf 6)$(tput bold)--- DIFFSTATIC ---$(tput sgr0)"
              difft "$file1" "$file2" || true
              echo "$(tput setaf 6)$(tput bold)--- END DIFFSTATIC ---$(tput sgr0)"
            else
              echo "$(tput setaf 6)$(tput bold)--- DIFF ---$(tput sgr0)"
              git diff --ignore-cr-at-eol --no-index --line-prefix="  " --word-diff=color -U0 --color=always "$file1" "$file2" 2>/dev/null | tail -n +5 || true
              echo "$(tput setaf 6)$(tput bold)--- END DIFF ---$(tput sgr0)"
            fi
            echo
          }

          # Determine file type and compilation/execution method
          if [ -f "$program_name.c" ]; then
            binary_to_cleanup="$program_name"
            echo "C file: $program_name.c"
            source_file="$program_name.c"
            compiler="$CC"
            if [ -z "$compiler" ]; then
              compiler="gcc"
            fi
            
            # Compile
            $compiler -ggdb "$source_file" -o "$program_name" -lm -Wall "''${@:3}"
             
            # Run
            if [ -f "c.in" ]; then
              ./"$program_name" < c.in > /tmp/tp_out || true
            else
              echo "c.in not found, running without input"
              ./"$program_name" > /tmp/tp_out || true
            fi
            
          elif [ -f "$program_name.cpp" ]; then
            binary_to_cleanup="$program_name"
            echo "C++ file: $program_name.cpp"
            source_file="$program_name.cpp"
            compiler="$CXX"
            if [ -z "$compiler" ]; then
              compiler="g++"
            fi
            
            # Compile
            $compiler -ggdb "$source_file" -o "$program_name" -lm -Wall "''${@:3}"
            
            # Run
            if [ -f "cpp.in" ]; then
              ./"$program_name" < cpp.in > /tmp/tp_out || true
            else
              echo "cpp.in not found, running without input"
              ./"$program_name" > /tmp/tp_out || true
            fi
            
          elif [ -f "$program_name.java" ]; then
            echo "Java file: $program_name.java"
            
            # Run Java
            if [ -f "java.in" ]; then
              java "$program_name.java" < java.in > /tmp/tp_out || true
            else
              echo "java.in not found, running without input"
              java "$program_name.java" > /tmp/tp_out || true
            fi
            
          else
            echo "No source file found for '$program_name'"
            echo "   Valid Options: $program_name.c, $program_name.cpp, $program_name.java"
            exit 1
          fi

          sync

          # Show output
          echo "$(tput setaf 4)$(tput bold)--- OUTPUT ---$(tput sgr0)"
          cat /tmp/tp_out
          echo "$(tput setaf 4)$(tput bold)--- END OUTPUT ---$(tput sgr0)"

          # Compare with expected output if provided
          if [ -n "$expected_output" ]; then
            if [ -f "$expected_output" ]; then
              echo
              get_files_diff "$expected_output" "/tmp/tp_out"
            else
              echo "Expected output file '$expected_output' not found"
            fi
          fi
        '';
      in
      {
        devShells.default = pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } rec {
          packages = with pkgs; [
            # Helpers
            mymake
            verde_run
            verde_download
            verde_rename_download

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
              cp ./verde/tp2/entrada.csv /tmp/disneyplus.csv
              export JAVA_TOOL_OPTIONS="${loadLombok}${prev}"
            '';
        };
      }
    );
}
