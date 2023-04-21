@REM 使用ffmpeg命令,把bmp转化为rgb24和yuv444
ffmpeg -i ./resource/rainbow_711x711.bmp -video_size 711x711 -pix_fmt rgb24 ./res/rainbow-711x711-bmp-rgb24.rgb