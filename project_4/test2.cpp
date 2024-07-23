#include <iostream>
#include <cstdlib>

int main()
{
    int light = 1;
    int abstcale = 1;

    std::string post = "curl -X POST -d'data=' https://Doki.pythonanywhere.com/files";
    std::string data = std::to_string(light) + ":" + std::to_string(abstcale);
    post.insert(post.find('=')+1,data);
    const char *post_c = post.c_str();
    system(post_c);
    return 0;
}