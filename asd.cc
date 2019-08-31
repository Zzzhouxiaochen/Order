// capacity        
size_t Size()const {
	return _size; 
}
size_t Capacity()const  {  
	return _capacity; 
}
 
bool Empty()const {  
	return 0 == _size; 
}
 
void Resize(size_t newSize, char c = char()){
	if (newSize > _size) {                
		// 如果newSize大于底层空间大小，则需要重新开辟空间 
		if (newSize > _capacity) {  
			Reserve(newSize);  
		}
		memset(_str + _size, c, newSize - _size); 
	}
	_size = newSize;
	_str[newSize] = '\0';        
}
 
 
 ///////对自定义的string类进行测试 
 void TestMyStringString1() {    
 MyString::String s1;    
 MyString::String s2("hello MyString");    
 MyString::String s3(s2);
    s1 = s3;    
	cout << s1 << endl;    
	cout << s2 << endl;    
	cout << s3 << endl; }
 
void TestMyStringString2() {    
	MyString::String s1("hello");    
	s1.PushBack(' ');    
	s1.PushBack('b');    
	s1.Append(1, 'i');    
	s1 += 't';    
	cout << s1 << endl;
	cout << s1.Size() << endl; 
	cout << s1.Capacity() << endl;
	// 利用迭代器打印string中的元素    
	auto it = s1.Begin();    
	while (it != s1.End())	{
		cout << *it++;    
	}
	cout << endl;
	MyString::String s2("hello world!!!");
	s1.Swap(s2);
	cout << s1 << endl;
	cout << s2 << endl; 
}
void TestMyStringString3() {
	
	MyString::String s("hello");
	cout << s << endl;
	cout << s.Size() << endl;
	cout << s.Capacity() << endl;
	
    s.ReSize(10, 'a');
	cout << s << endl;
	cout << s.Size() << endl;
	cout << s.Capacity() << endl;
	
    s.ReSize(20);
	cout << s << endl;
	cout << s.Size() << endl;
	cout << s.Capacity() << endl;
	
    s.ReSize(5);
	cout << s << endl;
	cout << s.Size() << endl;
	cout << s.Capacity() << endl;
 
    s.Reserve(50);
	cout << s << endl;
	cout << s.Size() << endl;
	cout << s.Capacity() << endl;
}

void TestListIterator1() {
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }; 
	list<int> l(array, array+sizeof(array)/sizeof(array[0]));
 
	auto it = l.begin(); 
	while (it != l.end()) {
		// erase()函数执行后，it所指向的节点已被删除，因此it无效，在下一次使用it时，必须先给其赋值
		l.erase(it);
		++it; 
	} 
}

void TestListIterator1() {
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }; 
	list<int> l(array, array+sizeof(array)/sizeof(array[0]));
 
	auto it = l.begin(); 
	while (it != l.end()) {
		l.erase(it++);	 // it = l.erase(it); 
	} 
}
 