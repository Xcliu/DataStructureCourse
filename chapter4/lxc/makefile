#export CPLUS_INCLUDE_PATH=/Users/liuxingchen/work/DataStructureCourse/DataStructureHomework/chapter2/
CC = g++  
CFLAGS = -Wall -O2 -std=c++11 -I../../common_library/# 指定头文件首先搜索的路径

Filename=gen_list_test
End=.cpp
$(Filename): $(Filename)$(End) ../../common_library/mystd.cpp 
	@$(CC) $(CFLAGS) -o $@  $^ #-I ../../DataStructureHomework/chapter2




git_up:
	@git pull;git add -A;git status;git commit -m "ex";git push origin master
