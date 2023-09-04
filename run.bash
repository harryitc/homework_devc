#!/bin/bash

# Danh sách các thư mục chứa mã nguồn C++
folders=(
    "CTDL_GT/node" 
    "CTDL_GT/stack"
    )

# Biên dịch và chạy các tệp C++
for folder in "${folders[@]}"; do
    for file in "$folder"/*.cpp; do
        if [ -f "$file" ]; then
            filename=$(basename "$file")
            filename_noext="${filename%.cpp}"
            executable="$folder/$filename_noext.exe"
            
            g++ "$file" -o "$executable"
            
            if [ $? -eq 0 ]; then
                echo "Biên dịch $file thành công và lưu tại $executable"
                echo "Chạy $executable:"
                "$executable"
            else
                echo "Lỗi khi biên dịch $file"
            fi
        fi
    done
done
