#include<iostream>
#include<unordered_map>
#include <cassert>
#include <cstdint>
#include<vector>
#include<random>

template<typename T>
void display(std::vector<T> &in){
	for(const auto& x:in){
		std::cout<<x<<" ";
	}
	std::cout<<std::endl;

}
template<typename U,typename V>
void display(std::unordered_map<U,V> &in){
	for(const auto& x:in){
		std::cout<<x.first<<" "<<x.second<<"\n";
	}
	std::cout<<std::endl;

}
class DataInitializer{
	public:
		virtual void initialize() = 0;
		virtual ~DataInitializer() = default;
};

class RandomDataInitializer:public DataInitializer{
	private:
		size_t num_elements;
		std::vector<int> data;
	public:
		explicit RandomDataInitializer(size_t elements): num_elements(elements) {}
		void initialize() override{
			data.clear(); // Clear existing data;
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(1,100);

			for(size_t i = 0;i<num_elements;i++){
				data.push_back(dist(gen));
			}

			std::cout << "Random data Generated"<<std::endl;

			for(const auto& num:data){
				std::cout<<num<<" ";
			}
			std::cout<<std::endl;


		}
	// Destructor
		~RandomDataInitializer() override {
		};
};


class Tensor{
	private:
//		cutensorMgHandle_t handle ;
		std::vector<float> h_data;
		std::vector<int64_t> extents;
		std::vector<int32_t> modes;
		std::vector<int64_t> blocksizes;
		std::vector<int32_t> deviceCount;


	public:
		//Tensor() = default;
		Tensor(const  std::unordered_map<int32_t,int64_t>  &extents,const std::vector<int32_t> &modes,const std::unordered_map<int32_t,int64_t> &blocksizes,std::unordered_map<int32_t,int32_t> &devicecounts){
		//Tensor(const cutensorMgHandle_t &handle,const  std::unordered_map<int32_t,int64_t>&& extents,const std::unordered_map<int32_t,int64_t>&& modes,const std::unordered_map<int32_t,int64_t>&& blocksizes,std::vector<int32_t> deviceCount){
		//this->handle = handle;
		
		
		this->modes = modes;
		for(auto &mode:modes){
			this->extents.push_back(extents.at(mode));
			this->blocksizes.push_back(blocksizes.at(mode));
			this->deviceCount.push_back(devicecounts.at(mode));
		}	
		}
		void set_data(std::vector<float> &data){
			this->h_data=data;
		}

		void print_info(){

			std::cout<<"Extents:\n";
			display(this->extents);
			std::cout<<"Modes:\n";
			display(this->modes);
			std::cout<<"Blocksizes:\n";
			display(this->blocksizes);
			std::cout<<"DeviceCount\n";
			display(this->deviceCount);

		}

		
};
		



int main(int argc,char** argv){
	//Create an instance

	RandomDataInitializer init(10);

	//Initialize data
	init.initialize();

	//Create Tensor Descriptor
	
	std::unordered_map<int32_t, int64_t> extent;
	extent['i'] = 4096;
	extent['j'] = 4096;
	extent['k'] = 4096;

	std::unordered_map<int32_t, int64_t> blocksize;
	blocksize['i'] = 2048;
	blocksize['j'] = 2048;
	blocksize['k'] = 2048;

	std::unordered_map<int32_t, int32_t> deviceCount;
	deviceCount['i'] = 2;
	deviceCount['j'] = 2;
	deviceCount['k'] = 2;

	std::vector<int32_t> modesA {'i', 'k'};
	std::vector<int32_t> modesB {'k', 'j'};
	std::vector<int32_t> modesC {'i', 'j'};
	//extents,modes,blocksizes,deviceCount
	Tensor mytensor(extent,modesA,blocksize,deviceCount);
	mytensor.print_info();
	return 0;

}


