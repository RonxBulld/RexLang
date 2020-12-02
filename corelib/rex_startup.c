/*
 * 程序入口函数代码文件
 * 编译为目标代码文件，由连接器连接到主程序
 */

extern int RexStartup(void) ;

int main(int argc, char **argv) {
    int EC = 0;
    EC = RexStartup() ;
    return EC;
}
