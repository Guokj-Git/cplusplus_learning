//��Ļ���˼�룺���ݳ���Data Abstraction�ͷ�װEncapsulation�����ݳ�����һ�������ڽӿ�Interface��ʵ��Implementation����ļ�����
	//ע�����ݽṹ�����ݳ��������

//7.1 ���������������

struct Sales_data{ //ʹ��class��struct��Ψһ���𣺵�һ������˵��������ǰ��class�г��ֵĳ�Ա����private�ģ�struct��Ϊpublic��
	//�����Ԫ��friend�������������ⶨ��ĺ�������ʹ��private���ݳ�Ա
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::ostream &print(std::ostream&, const Sales_data&);
	friend std::istream &read(std::istream&, Sales_data&);
	
public: //����˵����������ĳ�Ա����ȫ����Χ���ʡ�
	//���캯��
	Sales_data() = default; //�൱�ںϳ�Ĭ�Ϲ��캯����ǰ����ҪΪ�������͵����ݳ�Ա�ṩ��ʼֵ��
	Sales_data(const std::string &s) :bookNo(s) {} //���캯���ĳ�ʼֵ�б��������ݳ�Աδ������������ʱ���佫�Զ��Ժϳ�Ĭ�Ϲ��캯�����棩
	Sales_data(const std::string &s, unsigned n, double p) :
	bookNo(s), units_sold(n), revenue(p*n) {}
	Sales_data(std::istream&);
	//����Sales_data����Ĳ���
	std::string isbn() const { return bookNo; } //1)��ʽ�βΣ�ָ����øú����Ķ��󣬵������в���ʾ��
												//	return bookNo �൱�� return this->bookNo, this Ϊ��ʽ�βΡ�
												//2)������Ա�������ڲ����б�����const, ��ʾ����ʽ�β�����Ϊָ������ָ�룬
												//	���isbn()���ܸı�������Ķ�������ݡ�
	Sales_data& combine(const Sales_data&);
private: //����˵����������ĳ�Ա���ɱ���ĳ�Ա�������ʣ����ܱ�ʹ�ø���Ĵ�����ʡ�
		 //����˵�����������ڳ��ֶ�Ρ�
	double avg_price() const;
	//���ݳ�Ա
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;

};

//�����ⶨ�幹�캯��
Sales_data::Sales_data(std::istream& is) {
	read(is, *this);
}

//�����ⲿ�����Ա����
double Sales_data::avg_price() const{
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}
Sales_data& Sales_data::combine(const Sales_data &rhs) { //combine rhs with the item who call the function
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

//Sales_data�ķǳ�Ա����
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) { //combine lhs and rhs, then return the conjunction of them
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}
std::ostream &print(std::ostream &os, const Sales_data &item) { //print the item to cout
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}
std::istream &read(std::istream &is, Sales_data &item) { //read the item from cin
	double price = 0.0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price*item.units_sold;
	return is;
}

class Screen {
public:
	typedef std::string::size_type pos;
	Screen() = default;
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), 
		contents(ht*wd, c) { }
	char get()const { return contents[cursor]; }
	inline char get(pos ht, pos wd)const;	//��ʽ��������������������ʹ�ã�
	Screen &move(pos r, pos c);				//Ҳ���ں����Ķ��崦ʹ��
	void some_member()const;
private:
	mutable size_t access_ctr;	//�ɱ����ݳ�Ա��mutable data member�����κγ�Ա����������const�������ھ��ɸı�����ֵ
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
};

void Screen::some_member()const {
	++access_ctr;
}

inline Screen &Screen::move(pos r, pos c) {
	pos row = r*width;
	cursor = row + c;
	return *this;
}

char Screen::get(pos r, pos c)const {
	pos row = r*width;
	return contents[row + c];
}

class Window_mgr{
private:
	std::vector<Screen> screens{ Screen(24,80,' ') };
};

void chap7()
{
	//������: ����isbn�������������۸�ͳ�Ƹ���ͼ������
	Sales_data total;
	if (read(std::cin, total)) {
		Sales_data trans;
		while (read(std::cin, trans)) {
			if (total.isbn() == trans.isbn())
				total=add(total, trans);
			else {
				print(std::cout, total) << std::endl;
				total = trans;
			}
		}
		print(std::cout, total) << std::endl;
	}
	else {
		std::cerr << "no data" << std::endl;
	}
}