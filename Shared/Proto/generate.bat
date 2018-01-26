setlocal

for %%f in (*.proto) do (
    echo Compiling %%f file
    "C:\Program Files\Focus\protobuf\bin\protoc.exe" --cpp_out=./ProtoCompiled/ %%f
)
