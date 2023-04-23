
@REM 使用ffplay命令，播放rgb24
@REM ffplay -pixel_format rgb24 -video_size 1010x1324 -i ./resource/libjpeg-turbo-test-image-rgb24.rgb
@REM ffplay -pixel_format rgb24 -video_size 1010x1324 -i ./resource/result_tirg_rgb24.rgb
ffplay -pixel_format rgb24 -video_size 1010x1324 -i ./resource/result_tirg2_rgb24.rgb
@REM ffplay -pixel_format rgb24 -video_size 1010x1324 -i ./jepg-resource/ffmpeg-libjpeg-turbo-test-image-rgg24.rgb