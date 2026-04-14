# Project Template

## Introduction

This is a project template for XU316 series board

## Configuration

This project uses XCommon Cmake and compatible with XMOS VSCode extension [XMOS XTC Tools](https://marketplace.visualstudio.com/items?itemName=xmos.xtc-tools).

## Build (Terminal)

```bash
cmake -G "Unix Makefiles" -B build
xmake -C build
```

## Run (Terminal)

```bash
xrun --xscope ./bin/template.xe
```

## Debug Commands

### Capture xscope probe

1. ```xrun --xscope --xscope-file debug/xscope.vcd ./bin/template.xe```

2. Open the captured files in GTKWave

3. ```gtkwave.exe debug/xscope.gtkw```

### Capture audio through xscope probe

1. Add a probe to xscope, having something like this
    ```xml
    <xSCOPEconfig ioMode="basic" enabled="true">
        <Probe name="CH0" type="CONTINUOUS" datatype="INT" units="mV" enabled="true"/>
    </xSCOPEconfig>
    ```

2. Ouput the audio data with
    ```xscope_int(probe_name, data);``` in a consistent interval

3. Compile program

4. ```xrun --xscope --xscope-file debug/xscope.vcd ./bin/template.xe```

5. ```python debug/vcd_to_wav.py debug/xscope.vcd 48000 32 0 debug/xscope.wav```

### Convert KingstVIS dump file into wav file

1. Capture the I2S data with KingstVIS

2. Export the I2S data to a txt file with KingstVIS

3. ```python debug/kingstvis_i2s_to_wav.py i2s_test.txt 48000 32 debug/i2s.wav```