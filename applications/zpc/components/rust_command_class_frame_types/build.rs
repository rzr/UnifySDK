///////////////////////////////////////////////////////////////////////////////
// # License
// <b>Copyright 2022  Silicon Laboratories Inc. www.silabs.com</b>
///////////////////////////////////////////////////////////////////////////////
// The licensor of this software is Silicon Laboratories Inc. Your use of this
// software is governed by the terms of Silicon Labs Master Software License
// Agreement (MSLA) available at
// www.silabs.com/about-us/legal/master-software-license-agreement. This
// software is distributed to you in Source Code format and is governed by the
// sections of the MSLA applicable to Source Code.
//
///////////////////////////////////////////////////////////////////////////////
use std::env;
use std::path::PathBuf;
use std::process::Command;

fn main() {
    let out_dir = env::var_os("OUT_DIR").unwrap();
    //TODO I'm not quite sure how to set this in a nice way
    //env::var_os("XML_FILE").unwrap();
    let xml = PathBuf::from("../zwave_command_classes/assets/ZWave_custom_cmd_classes.xml");
    assert!(xml.exists());

    let py = PathBuf::from("zwave_rust_cc_gen.py");
    assert!(py.exists());

    which::which("python3").expect("Python was not found");
    let _ = Command::new("python3")
        .arg(py.to_str().unwrap())
        .arg("--xml")
        .arg(&xml.to_str().unwrap())
        .arg("--outdir")
        .arg(&out_dir)
        .output()
        .expect(&format!("Failed to run python script {}", py.display()));
    // println!("cargo:rerun-if-changed=zwave_rust_cc_gen.py");
    println!("cargo:rerun-if-changed={}", py.to_str().unwrap());
    // there is an fingerprinting bug in cargo, the path is constructed wrong triggering rebuilds of this package
    // println!("cargo:rerun-if-changed={:?}", &format!("{}/{}",std::env::var("CARGO_MANIFEST_DIR").unwrap(), xml_file));
}