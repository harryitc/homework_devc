#!/bin/bash

# Danh sách các thư mục chứa mã nguồn C++
folders=(
    "CTDL_GT/node" 
    "CTDL_GT/stack"
    )
# folders=("CTDL_GT/stack" "other_folder_1" "other_folder_2")

# Vòng lặp qua từng thư mục
for folder in "${folders[@]}"; do
    # Tìm tất cả các tệp .cpp trong thư mục
    for file in "$folder"/*.cpp; do
        # Kiểm tra xem tệp tồn tại
        if [ -f "$file" ]; then
            # Lấy tên tệp và loại bỏ phần mở rộng .cpp
            filename=$(basename "$file")
            filename_noext="${filename%.cpp}"
            
            # Biên dịch tệp C++ thành tệp thực thi
            g++ "$file" -o "$folder/$filename_noext.exe"
            
            # Kiểm tra xem biên dịch thành công hay không
            if [ $? -eq 0 ]; then
                echo "Biên dịch $file thành công và lưu tại $folder/$filename_noext.exe"
            else
                echo "Lỗi khi biên dịch $file"
            fi
        fi
    done
done
