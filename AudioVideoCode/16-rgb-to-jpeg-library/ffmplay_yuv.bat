@REM 使用ffplay命令，yuv444和yuv420p
@REM ffplay -pixel_format yuv420p -video_size 1010x1324 -framerate 5 ./jepg-resource/ffmpeg-libjpeg-turbo-test-image-yuv420p.yuv
@REM ffplay -pixel_format yuv444p -video_size 1010x1324 -framerate 5 ./jepg-resource/ffmpeg-libjpeg-turbo-test-image-yuv444p.yuv
ffplay -pixel_format yuv420p -video_size 1010x1324 -framerate 5 ./resource/libjpeg-turbo-test-image-yuv420.yuv