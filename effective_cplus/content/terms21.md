# 条款21：必须返回对象时，别妄想返回其reference

- 绝不要返回pointer或reference指向一个local stack对象；

- 绝不要返回reference指向一个heap-allocated对象

- 绝不要返回pointer或reference指向一个local static对象而有可能同时需要多个这样的对象

当你必须在“返回一个reference和返回一个object”之间抉择时，你的工作就是挑出行为正确的那个，
就让编译器厂商为“尽可能降低成本”鞠躬尽瘁吧，你可以享受你的生活
