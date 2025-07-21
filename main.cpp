#include <iostream>
#include <cstdio> // std::removeを使用するため
#include <string>

using namespace std;

int main()
{
    string filepath;
    // ユーザーに削除したいファイルのパスを入力してもらう
    cout << "削除したいファイルのパスを入力してください: ";
    getline(cin, filepath);

    // 指定されたファイルを削除する
    if (remove(filepath.c_str()) == 0) {
        // 削除成功時のメッセージ
        cout << "ファイルを削除しました。" << endl;
    } else {
        // 削除失敗時のメッセージ
        cout << "ファイルの削除に失敗しました。" << endl;
    }
    return 0;
}