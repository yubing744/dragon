编码规则

1、如果一个对象的方法的返回值为 const 类型对象指针， 则说明返回的对象我们
可以用，但是不负责释放，如果返回的指针类型为非const类型指针，则需要调用者
手动释放。

2、dragon test files
http://oj1fqm2fl.bkt.clouddn.com/dragon_test.zip