{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
    buildInputs = [
        pkgs.cmake
        pkgs.glfw
        pkgs.glm
    ];

    shellHook = ''
        export CPLUS_INCLUDE_PATH="${toString ./.}/include"
    '';
}
