{ pkgs ? (import <nixpkgs> {})
, stdenv ? pkgs.stdenv
, gnumake ? pkgs.gnumake
}:

stdenv.mkDerivation rec {
  name = "hlibc";
  version = "0.0.1";

  src = ./../..;

  phases = [ "unpackPhase" "patchPhase" "checkPhase" "configurePhase" "installPhase" ];
  checkPhase = ''
    make gcctest -j1
  '';

  doCheck = true;

  hardeningDisable = ["all"];

  buildInputs = [ gnumake ];
}
