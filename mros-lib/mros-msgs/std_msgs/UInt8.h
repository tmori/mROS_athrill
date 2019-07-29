#ifndef _STD_MSGS_UINT8_H
#define _STD_MSGS_UINT8_H


static const int UINT8_MSG_ID = 5;

namespace std_msgs{
class UInt8{
public:
	uint8_t data;
  int dataSize(){return 1;}
  void memCopy(char *addrPtr){
    memcpy(addrPtr,&data,1);
  }
};
}

namespace message_traits
{
template<>
struct MD5Sum<UINT8_MSG_ID>
{
  static const char* value()
  {
    return "7c8164229e7d2c17eb95e9231617fdee";
  }

};

template<>
struct DataType<std_msgs::UInt8*>
{
  static const char* value()
  {
    return "std_msgs/UInt8";
  }

};

template<>
struct DataTypeId<std_msgs::UInt8*>
{
  static const int value()
  {
    return UINT8_MSG_ID;
  }

};

template<>
struct Definition<std_msgs::UInt8*>
{
	static const char* value()
	{
		return "int8 data\n\\n\
";
	}
};
}

namespace subtask_methods
{
  template<>
  struct CallCallbackFuncs<UINT8_MSG_ID>{
    static void call(void (*fp)(intptr_t), char *rbuf)
    {
      std_msgs::UInt8 msg;
      rbuf += 4;
      memcpy(&msg.data,rbuf,1);
      //msg.data = (int)rbuf[4];
      fp(&msg);
    }
  };
}

#endif