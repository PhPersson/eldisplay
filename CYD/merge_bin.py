Import("env", "projenv")
import subprocess, os

def merge_bin(source, target, env):
    esptool = os.path.join(
        env.subst("$PROJECT_PACKAGES_DIR"),
        "tool-esptoolpy", "esptool.py"
    )
    
    flash_args = [
        env.subst("$PYTHONEXE"), esptool,
        "--chip", "esp32", "merge_bin",
        "-o", env.subst("$BUILD_DIR/merged.bin"),
        "--flash_mode", "dio",
        "--flash_freq", "40m",
        "--flash_size", "4MB",
        "0x1000",  env.subst("$BUILD_DIR/bootloader.bin"),
        "0x8000",  env.subst("$BUILD_DIR/partitions.bin"),
        "0xe000",  os.path.join(
            env.subst("$PROJECT_PACKAGES_DIR"),
            "framework-arduinoespressif32", "tools", "partitions", "boot_app0.bin"
        ),
        "0x10000", env.subst("$BUILD_DIR/${PROGNAME}.bin"),
    ]
    result = subprocess.run(flash_args, capture_output=True, text=True)

env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", merge_bin)