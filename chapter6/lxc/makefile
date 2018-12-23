#export CPLUS_INCLUDE_PATH=/Users/liuxingchen/work/DataStructureCourse/DataStructureHomework/chapter2/
CC = g++  
CFLAGS = -Wall -O2 -std=c++11 #-I../../common_library/# 指定头文件首先搜索的路径

Filename=6.14
End=.cpp
$(Filename): $(Filename)$(End) #../../common_library/mystd.cpp 
	@$(CC) $(CFLAGS) -o $@  $^ #-I ../../DataStructureHomework/chapter2

name=6.19.go

go_run:
	go run $(name)


git_up:
	@git pull;git add -A;git status;git commit -m "chapter6";git push origin master
