# wave
Welcome to C++ library for making wave file.

## Usage

```cpp
#include "wave.hpp"
#include <math.h>
#define PI acos(-1)
int main(void)
{
    pcm wave(10);
    for(int i = 0; i < wave.size; i++)
    {
        double amp_left = sin(2 * PI * 0.25 / wave.fs * i);
        double amp_right = sin(2 * PI * 0.25 / wave.fs * i + PI / 2);
        double freq;
        if(i < wave.size * 1 / 10) freq = 261.626;
        else if(i < wave.size * 2 / 10) freq = 293.665;
        else if(i < wave.size * 3 / 10) freq = 329.628;
        wave.s[0][i] = amp_right * sin(2 * PI * freq / wave.fs * i);
        wave.s[1][i] = amp_left *  sin(2 * PI * freq / wave.fs * i);
    }
    wave.write("test.wav");
    return 0;
}
```
