# wave
Welcome to C++ library for making wave file.

## Usage

```cpp
#include "wave.hpp"
#include <math.h>
#define PI acos(-1)
int main(void)
{
    wave pcm(10);
    for(int i = 0; i < pcm.size; i++)
    {
        double amp_left = sin(2 * PI * 0.25 / pcm.fs * i);
        double amp_right = sin(2 * PI * 0.25 / pcm.fs * i + PI / 2);
        double freq;
        if(i < pcm.size * 1 / 10) freq = 261.626;
        else if(i < pcm.size * 2 / 10) freq = 293.665;
        else if(i < pcm.size * 3 / 10) freq = 329.628;
        pcm.s[0][i] = amp_right * sin(2 * PI * freq / pcm.fs * i);
        pcm.s[1][i] = amp_left *  sin(2 * PI * freq / pcm.fs * i);
    }
    pcm.write("test.wav");
    return 0;
}
```
## Reference
1. 青木 直史, "C言語ではじめる音のプログラミング―サウンドエフェクトの信号処理", オーム社, 2008
