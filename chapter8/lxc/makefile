################### for .cpp 
#export CPLUS_INCLUDE_PATH=/Users/liuxingchen/work/DataStructureCourse/DataStructureHomework/chapter2/
CC = g++  
CFLAGS = -Wall -O2 -std=c++11 #-I../../common_library/# 指定头文件首先搜索的路径
Filename=g_mtx_test
End=.cpp
$(Filename): $(Filename)$(End) #../../common_library/mystd.cpp 
	@$(CC) $(CFLAGS) -o $@  $^ #-I ../../DataStructureHomework/chapter2

##################### for .go
name=
go_run:
	go run $(name)

##################### for .git
git_up:
	@git pull;git add -A;git status;git commit -m "chapter8";git push origin master

