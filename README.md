# PowerMonkeyLoader
 A simple UEFI application helps launch PowerMonkey and start custom system boot image (e.g. Windows) automatically.

 This work could not have been created without the help of [VisualUEFI project](https://github.com/ionescu007/VisualUefi) and [PowerMonkey project](https://github.com/psyq321/PowerMonkey).

## Build
1. Clone the [VisualUEFI project](https://github.com/ionescu007/VisualUefi) repository and follow its instructions to build the prerequisites.
2. Clone the [PowerMonkey project](https://github.com/psyq321/PowerMonkey) repository and store its root directory directly in the root of the VisualUEFI repository, follow its instructions to build PowerMonkey, then put it in the EFI partition.
3. Clone this repository and store its root directory directly in the root of the VisualUEFI repository. After you finished these steps, the repository should looks like this:
    ```bash
    VisualUEFI
    ├── debugger/
    ├── EDK-II/
    ├── edk2/
    ├── openssl/
    ├── PowerMonkey/                           <--- PowerMonkey Workspace
    ├── PowerMonkeyLoader/                     <--- This repository
    │   ├── PowerMonkeyLoader/                 <--- Source Code
    │   │   ├── Config.c                       <--- Settings
    │   │   ├── PMLoader.c                     <--- Main Program
    │   │   └── ...
    │   ├── PowerMonkeyLoader.default.props
    │   ├── PowerMonkeyLoader.props
    │   ├── PowerMonkeyLoader.sln              <--- Visual Studio Solution File
    │   └── README.MD
    ├── Samples/
    └── ...
    ```
4. Open ```PowerMonkeyLoader.sln``` and edit device paths in ```Config.c```. To get the device paths of EFI images, you can go to the EFI Shell and type ```map```, then find the device path of EFI parititon use ```fsX:``` (X is the path shown in the ```map``` command) and ```ls``` command. Typical device paths of images looks like these:
    ```bash
    PciRoot(0x0)/Pci(0x2,0x0)/Pci(0x0,0x0)/NVMe(0x1,11-20-00-00-00-00-00-00)/HD(1,GPT,ABCDEFGH-1234-5678-ABCD-ABCDEFGHIJK,0x800,0x32000)/EFI/PowerMonkey/PowerMonkey.efi
    PciRoot(0x0)/Pci(0x2,0x0)/Pci(0x0,0x0)/NVMe(0x1,11-20-00-00-00-00-00-00)/HD(1,GPT,ABCDEFGH-1234-5678-ABCD-ABCDEFGHIJK,0x800,0x32000)/EFI/Microsoft/Boot/bootmgfw.efi
    ```
5. Build the project directly in Visual Studio. This process shall generate no warnings or errors. The result should be an EFI executable ```/PowerMonkeyLoader/x64/Release/PowerMonkeyLoader.efi```

## Installation
Copy the EFI executable to the EFI partition and add the boot entry just like any other EFI images.