package main
import("bufio";"fmt";"os")
func main(){in:=bufio.NewReader(os.Stdin);var n int;fmt.Fscan(in,&n);a,b:=0,1000000000;for i:=0;i<n;i++{var t int;fmt.Fscan(in,&t);u:=t;if u<0{u=-u};if u<b||u==b&&t>a{b=u;a=t}}if b<1000000000{fmt.Print(a)}else{fmt.Print(0)}}