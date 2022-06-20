# Template project for the Artery AT32F403A

Template CMake project for the Artery [AT32F403A Series](https://www.arterychip.com/en/product/AT32F403A.jsp) based on the ```01-template``` example from  [WeAct TC Studio's GitHub](https://github.com/WeActTC/WeActStudio.BlackPill/tree/main/Examples/AT32F403A/Keil/01-template)

Developed on the ```WeAct TC Studio Blackpill (AT32F403A)``` evaluation board obtainable from Aliexpress.

## Building:

i.  Create build system: ```cmake -DCMAKE_BUILD_TYPE=Debug -B build```

ii. Build firmware: ```cmake --build build --target all```

## SPIM XIP:

i.  The project also demos the use of SPIM (QSPI SPI Flash eXecute-in-place). This requires the use of a flash loader that can flash to the SPIM (see further below for details)

ii. To turn off the use of SPIM and use *only* the regular MCU flash, comment out the call to ```spim_init()``` in ```main.c```, and change the declaration of ```led_toggle()``` in ```board.h``` to use the declaration *without* ```__attribute___```

iii.  The SPI Flash used in the example is a Winbond W25Q128JV and the parameters set in ```spim_init()``` are appropriate for this memory part per the AT32F403A [datasheet](https://www.arterychip.com/en/product/AT32F403A.jsp#Resource) (Type 2).

## Uploading:

i.  Assuming that SPIM XIP is not used then the firmware binary can be uploaded via DFU.

ii. To use ```OpenOCD``` a custom build is required. The appropriate patch can be found in the file ```at32f403a.cfg```, and build instructions from the OpenOCD [github](https://github.com/openocd-org/openocd)

## Segger JLink:

Segger JLink can be extended via the [Open Flashloader](https://wiki.segger.com/Open_Flashloader) framework to allow flashing to AT32F403A parts including any SPIM memory present

i. Download the Keil 5 pack from the AT32F403A [resources](https://www.arterychip.com/en/product/AT32F403A.jsp#Resource) page, and extract all the files. 

ii. Extract the AT32F403A specific files with ```tar zxvf ArteryTek.AT32F403A_407_DFP.2.0.8.pack``` (note: version numbers may change)

iii. Find (or create) the JLinkDevices directory:
```
Windows: C:\Users\<USER>\AppData\Roaming\SEGGER\JLinkDevices
Linux: $HOME/.config/SEGGER/JLinkDevices
macOS: $HOME/Library/Application Support/SEGGER/JLinkDevices
```

iv. Create a directory ```AT``` underneath this directory, e.g. ```.../SEGGER/JLinkDevices/AT/```

v. Copy all the ```*.FLM``` files from the ```Flash``` directory of the ```ArteryTek.AT32F403A_407_DFP.2.0.8.pack``` file to the ```.../SEGGER/JLinkDevices/AT/``` directory

vi. Finally create a file called ```JLinkDevices.xml``` in the ```.../SEGGER/JLinkDevices``` directory with the following content:
```
<DataBase>
 <Device>
    <ChipInfo Vendor="Artery" Name="AT32F403AxG" WorkRAMAddr="0x20000000" WorkRAMSize="0x18000" Core="JLINK_CORE_CORTEX_M4" />
    <FlashBankInfo Name="Internal Flash Bank 1" BaseAddr="0x08000000" MaxSize="0x100000" Loader="AT/AT32F403A_1024.FLM" LoaderType="FLASH_ALGO_TYPE_OPEN" AlwaysPresent="1" />
    <FlashBankInfo Name="QSPI SPIM Flash" BaseAddr="0x08400000" MaxSize="0x1000000" Loader="AT/AT32F403A_EXT_TYPE2_REAMP1_GENERAL.FLM" LoaderType="FLASH_ALGO_TYPE_OPEN" />
  </Device>
</DataBase>
```

vii. Adjust parameters ```MaxSize``` and ```Loader``` to reflect actual MCU and SPI Flash used (e.g. Type and Remap). If no SPI Flash then the relevant ```FlashBankInfo``` line can be removed. Multiple ```Device``` blocks can be added to differentiate devices.
