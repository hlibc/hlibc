{ pkgs ? (import <nixpkgs> {})
, stdenv ? pkgs.stdenv
, gnumake ? pkgs.gnumake
}:

stdenv.mkDerivation rec {
  name = "hlibc";
  version = "0.0.1";

  src = ./.;

  phases = [ "unpackPhase" "checkPhase" "configurePhase" "installPhase" ];
  checkPhase = ''
    make gcctest
  '';

  doCheck = true;

  ARCH=nixpkgs.stdenv.targetPlatform.platform.kernelArch;

  hardeningDisable = ["all"];

  buildInputs = [ gnumake ];
}
