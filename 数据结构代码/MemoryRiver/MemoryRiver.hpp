#ifndef BPT_MEMORYRIVER_HPP
#define BPT_MEMORYRIVER_HPP

#include <fstream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

template<class T, int info_len = 2>
class MemoryRiver {
private:
    /* your code here */
    fstream file;
    string file_name;
	int avai = 0;
    int sizeofT = sizeof(T);
public:
    MemoryRiver() = default;

    MemoryRiver(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "") {
        if (FN != "") file_name = FN;
        file.open(file_name, std::ios::out);
        int tmp = 0;
        for (int i = 0; i < info_len; ++i)
            file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
        file.close();
    }

    //������n��int��ֵ����tmp��1_base
    void get_info(int &tmp, int n) {
        if (n > info_len) return;
		file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
		file.seekg(sizeof(int) * (n - 1));
		file.read(reinterpret_cast<char*>(&tmp), sizeof(int));
		file.close();
        /* your code here */
    }

    //��tmpд���n��int��λ�ã�1_base
    void write_info(int tmp, int n) {
        if (n > info_len) return;
		file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
		file.seekp(sizeof(int) * (n - 1));
		file.write(reinterpret_cast<char*>(&tmp), sizeof(int));
		file.close();

        /* your code here */
    }

    //���ļ�����λ��д�������t��������д���λ������index
    //λ��������ζ�ŵ�������ȷ��λ������index�����������������ж���˳�����ҵ�Ŀ�������в���
    //λ������index����ȡΪ����д�����ʼλ��
    int write(T &t) {
        /* your code here */
		int tmp;
		file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
		if (!avai)
		{
			file.seekp(0, std::ios::end);
			tmp = file.tellp();
			int x = 0;
			file.write(reinterpret_cast<char*>(&x), sizeof(int));
			
		}
		else
		{
			tmp = avai;
			file.seekg(avai);
			file.read(reinterpret_cast<char*>(&avai), sizeof(int));
			file.seekp(tmp + sizeof(int));

		}

		file.write(reinterpret_cast<char*>(&t), sizeofT);
		file.close();
		return tmp;

    }

    //��t��ֵ����λ������index��Ӧ�Ķ��󣬱�֤���õ�index������write��������
    void update(T &t, const int index) {
        /* your code here */
		file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
		file.seekp(index + sizeof(int));
		file.write(reinterpret_cast<char*>(&t), sizeofT);
		file.close();

    }

    //����λ������index��Ӧ��T�����ֵ����ֵ��t����֤���õ�index������write��������
    void read(T &t, const int index) {
        /* your code here */
		file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
		file.seekg(index + sizeof(int));
		file.read(reinterpret_cast<char*>(&t), sizeofT);
		file.close();

    }

    //ɾ��λ������index��Ӧ�Ķ���(���漰�ռ����ʱ���ɺ��Դ˺���)����֤���õ�index������write��������
    void Delete(int index) {
        /* your code here */
		file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
		file.seekp(index);
		file.write(reinterpret_cast<char*>(&avai), sizeof(int));
		avai = index;
		file.close();
    }
};


#endif //BPT_MEMORYRIVER_HPP