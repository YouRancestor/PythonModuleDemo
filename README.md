# Python C Extention Demo
## 资料
- [Python C API 文档](https://docs.python.org/3/contents.html)
- Python C Extention 模板：[cpython](https://github.com/python/cpython/tree/v3.7.0)/Modules/xxmodule.c
## 用法
- 将 test.cpp 编译为动态库，命名为xx.so (名称xx须C代码中导出函数的命名一致)
- 将 xx.so 部署于 PyType.py 同级目录(部署位置须与 PyType.py 中的 import 指定相对位置一直，xx.so 等价于 xx.py)
- 执行 python3 PyType.py
## 内容
- 编写 Python 脚本定义类型 PyType。
- 根据 Python C API 文档和源码模板，编写test.cpp，实现 xx.Pass 函数，C 代码接受 PyType 类型对象并解析其属性。
- xx.efficiencyList 函数测试对比 PyList, std::list, std::vector 等容器的 Append, Random Access, Insert 等操作的执行效率。