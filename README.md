# pc-beeper



------



Tiny console utility runs on windows that beeps motherboard speaker via WinRing0 driver IO port read/write feature. This utility only support hardware platforms that have **System Speaker** device (Some laptops may lack this device). 

You can check out this in Device Manager: Set **View** to **Resources by type**, then select **Input/Output (IO)**, checkout port 0x61, it should be **System Speaker**, otherwise this utility won't work on your platform. 

How it works:

​	https://wiki.osdev.org/PC_Speaker

​	https://wiki.osdev.org/Programmable_Interval_Timer

------



<u>**ABSOLUTELY NO WARRANTIES, USE ON YOUR OWN RISK.**</u>



-----



Build: Microsoft Visual Studio 2017 Community

Run: Microsoft Visual C++ 2015/2017 Runtime is required

Usages:

​	-f frequency to beep, default goes to 440Hz

​	-d beep durations, in ms, default is 1000ms



------

```
MIT License

Copyright (c) 2018 cocafehj@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

