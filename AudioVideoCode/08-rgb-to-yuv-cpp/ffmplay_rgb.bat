@REM 使用ffmpeg命令,把bmp转化为rgb24和yuv444
@REM ffmpeg -i ./res/rainbow-700x700.bmp -video_size 711x711 -pix_fmt rgb24 ./res/rainbow-bmp-rgb24.rgb
@REM ffmpeg -i ./res/rainbow-700x700.bmp -video_size 711x711 -pix_fmt yuv444p ./res/rainbow-bmp-yuv444p.yuv

@REM 使用ffplay命令，播放rgb24和yuv444
@REM ffplay -pixel_format rgb24 -video_size 711x711 -i ./res/rainbow_711x711_rgb24.rgb
@REM ffplay -pixel_format rgb24 -video_size 711x711 -i ./res/rainbow_711x711_copy_rgb24.rgb

@REM ffplay -pixel_format rgb24 -video_size 711x711 -i ./res2/rainbow-_711x711_bmp_rgb24.rgb

@REM ffplay -pixel_format rgb24 -video_size 711x711 -i ./resource/rainbow_711x711_yuv444p_to_rgb24.rgb