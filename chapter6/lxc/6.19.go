package main

import(
	"ht"
	"fmt"
)
func main(){
	hash_tab:=ht.New(7)
	
	//4和f的Assic码正好差50，
	//如果这里的长度是50的因数会导致“4th”和“fifth”在同一个link_list

	hash_tab.Put("first","bear")
	hash_tab.Put("second","monkey")
	hash_tab.Put("third","bee")
	hash_tab.Put("4th","human")
	hash_tab.Put("fifth","monkey")
	
	hash_tab.ForEach( func(a *(ht.Item)){
		fmt.Println(ht.Get_key(a))
		}
	)

	println(hash_tab.Size)

}