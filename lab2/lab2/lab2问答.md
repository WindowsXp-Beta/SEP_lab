# lab2问答

```c++
int start, end;
char comma, type = ' ';
stringstream ss(cmd);//用cmd初始化stringstream
ss >> start;//读入start
if (ss.eof()) {//如果读到end of file了，即读完了，即只有一个字符
	cmdNull(start);
	return;
}
ss >> comma >> end >> type;//跳过逗号，读入end和type
if (ss.good()) {//如果上面的各项都顺利读入，即没有空项
	if (type == 'n') {
		cmdNumber(start, end);
		return;
	} else if (type == 'd') {
		cmdDelete(start, end);
		return;
	}
}
```

