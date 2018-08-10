# SoySauce

一个丑陋的对Raft一致性算法的实现，戏称为“酱油（Soy Sauce）”。

Raft算法的中文翻译版请见 
https://github.com/maemual/raft-zh_cn/blob/master/raft-zh_cn.md

本项目基本实现了Raft算法除了“集群成员变化”和“日志压缩”外所有的内容。src/main.cpp测试了一个简单的服务器的开关运行。config文件夹中的s.json是客户端配置实例，s1.json、s2.json、s3.json是三个服务器端的配置实例。

本项目在Ubuntu 16.04下实现，依赖于cmake，boost，grpc和protocol buffers等工具。

2018.8.10
