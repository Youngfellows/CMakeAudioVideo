@REM 使用ffmpeg命令,把bmp转化为rgb24和yuv444
@REM ffmpeg -i ./res/rainbow-700x700.bmp -video_size 711x711 -pix_fmt rgb24 ./res/rainbow-bmp-rgb24.rgb
@REM ffmpeg -i ./res/rainbow-700x700.bmp -video_size 711x711 -pix_fmt yuv444p ./res/rainbow-bmp-yuv444p.yuv

@REM 使用ffplay命令，播放rgb24和yuv444
@REM ffplay -pixel_format rgb24 -video_size 711x711 -i ./res/rainbow-bmp-rgb24.rgb
@REM ffplay -pixel_format yuv444p -video_size 711x711 -framerate 5 ./res/rainbow-bmp-yuv444p.yuv
@REM ffplay -pixel_format yuv420p -video_size 711x711 -framerate 5 ./res/rainbow-bmp-yuv420p.yuv
@REM ffplay -pixel_format yuv444p -video_size 711x711 -framerate 5 ./resource/rainbow-rgb24-to-yuv444p.yuv
@REM ffplay -pixel_format yuv420p -video_size 700x700 -framerate 5 ./resource/rainbow-700x700-rgb24-toyuv420p.yuv
ffplay -pixel_format yuv420p -video_size 700x700 -framerate 5 ./resource/rainbow-700x700-yuv420p.yuv
@REM ffplay -pixel_format yuv444p -video_size 711x711 -framerate 5 ./resource/rainbow-700x700-yuv420-to-yuv444.yuv