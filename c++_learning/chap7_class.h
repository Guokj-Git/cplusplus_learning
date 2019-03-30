//��Ļ���˼�룺���ݳ���Data Abstraction�ͷ�װEncapsulation�����ݳ�����һ�������ڽӿ�Interface��ʵ��Implementation����ļ�����
	//ע�����ݽṹ�����ݳ��������

//7.1 ���������������

struct Sales_data{
	//����Sales_data����Ĳ���
	std::string isbn() const { return bookNo; }//1)��ʽ�βΣ�ָ����øú����Ķ��󣬵������в���ʾ��
											   //	return bookNo �൱�� return this->bookNo, this Ϊ��ʽ�βΡ�
											   //2)������Ա�������ڲ����б�����const, ��ʾ����ʽ�β�����Ϊָ������ָ�룬
											   //	���isbn()���ܸı�������Ķ�������ݡ�
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	//���ݳ�Ա
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};
//�����ⲿ�����Ա����
double Sales_data::avg_price() const{
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}
Sales_data& Sales_data::combine(const Sales_data &rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}
//Sales_data�ķǳ�Ա����
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data);
