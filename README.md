# TseytinTransformation
This repository implements the Tseytin Transformation in order to convert the .bench to .cnf file.

The tool uses Tseytin Tranformation in order to transform the .bench file into .cnf file. 
The gates supported by .bench file and supported by the tool are,

     Supported Gates for BENCH Format
     -------------------------------------------------------
     syntax                   gate type
     -------------------------------------------------------
     INPUT                    primary input
     OUTPUT                   primary output
     AND                      and gate
     NAND                     nand gate
     OR                       or gate
     NOR                      nor gate
     XOR                      2 input exclusive-or gate
     BUFF or BUF              buffer
     NOT                      inverter
      -------------------------------------------------------

## How to run the tool

Zip and download the code. From the source folder invoke a terminal.
In the cmd type,
```
make all.
```

Copy your .bench file in to the folder containing the source files run the command,
```
./tseytinTransform <*.bench>
```
