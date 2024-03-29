#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class wave
{
public:
    const long fs = 44100; // Sampling rate
    const short bits = 16; // Quantization precision
    const short chs = 2; // Number of channels
    size_t size; // Length of sound wave array at each channel
    size_t currentIndex = 0;
    double** s; // Sound arraies, s[0]:right, s[1]:left
    wave(const double sec)
    {
        this->size = sec * this->fs;
        this->s = (double**)calloc(this->chs, sizeof(double**));
        for (int ch = 0; ch < this->chs; ch++)
        {
            this->s[ch] = (double*)calloc(this->size, sizeof(double));
        }
    }
    ~wave()
    {
        for (int ch = 0; ch < this->chs; ch++)
        {
            free(this->s[ch]);
        }
        free(this->s);
    }
    void write(const char* filename)
    {
        FILE* fp;
        fp = fopen(filename, "wb");
        if (fp == nullptr)
        {
            printf("*** Error this->write *******************\n");
            printf(" '%s' was not opened.\n", filename);
            printf("****************************************\n");
            exit(1);
        }

        long riff_chunk_size = 36 + this->size * this->bits / 8 * this->chs;
        long fmt_chunk_size = 16;
        short fmt_wave_format_type = 1;
        long fmt_bytes_per_sec = this->fs * this->bits / 8 * this->chs;
        short fmt_block_size = this->bits / 8 * this->chs;
        long data_chunk_size = this->size * this->bits / 8 * this->chs;
        
        fwrite("RIFF", 1, 4, fp);
        fwrite(&riff_chunk_size, 4, 1, fp);
        fwrite("WAVE", 1, 4, fp);
        fwrite("fmt ", 1, 4, fp);
        fwrite(&fmt_chunk_size, 4, 1, fp);
        fwrite(&fmt_wave_format_type, 2, 1, fp);
        fwrite(&this->chs, 2, 1, fp);
        fwrite(&this->fs, 4, 1, fp);
        fwrite(&fmt_bytes_per_sec, 4, 1, fp);
        fwrite(&fmt_block_size, 2, 1, fp);
        fwrite(&this->bits, 2, 1, fp);
        fwrite("data", 1, 4, fp);
        fwrite(&data_chunk_size, 4, 1, fp);
     
        double norma = pow(2, this->bits - 1);
        for (int n = 0; n < this->size; n++)
        {
            for (int ch = 0; ch < this->chs; ch++)
            {
                double _s = this->s[ch][n];
                if (_s > 1) // Clipping (Limit the absolute value to be 1)
                {
                    _s = 1;
                }
                else if (_s < -1)
                {
                    _s = -1;
                }
                short data = _s * norma; 
                fwrite(&data, this->bits / 8, 1, fp); // Write sound data
            }
        }
        fclose(fp);
    }
};

class scale
{
public:
    constexpr static  double C4 = 261.626;//do
    constexpr static  double D4 = 293.665;//re
    constexpr static  double E4 = 329.628;//mi
    constexpr static  double F4 = 349.228;//fa
    constexpr static  double G4 = 391.995;//sol
    constexpr static  double A4 = 440.000;//la
    constexpr static  double B4 = 493.883;//si
    constexpr static  double C5 = 523.251;//do
    constexpr static  double D5 = 587.330;//re
    constexpr static  double E5 = 659.255;//mi
    constexpr static  double F5 = 698.456;//fa
    constexpr static  double G5 = 783.991;//sol
};
