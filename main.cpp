#include <iostream>
#include <cstdio> // std::removeを使用するため
#include <string>
#include <regex>
#include <dirent.h> // ディレクトリ操作用
#include <sys/stat.h> // ファイル属性取得用

using namespace std;


// 指定ディレクトリ以下を再帰的に探索し、ファイル名が正規表現に一致するファイルを削除する関数
void remove_files_recursive(const string& dirpath, const regex& re, int& deleted, int& failed) {
    DIR* dir = opendir(dirpath.c_str()); // ディレクトリを開く
    if (dir == NULL) {
        cerr << "ディレクトリを開けません: " << dirpath << endl;
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        string filename = entry->d_name;
        if (filename == "." || filename == "..") continue; // カレント・親ディレクトリはスキップ
        string fullpath = dirpath + "/" + filename;
        struct stat st;
        if (stat(fullpath.c_str(), &st) != 0) continue; // ファイル情報取得失敗はスキップ
        if (S_ISDIR(st.st_mode)) {
            // サブディレクトリなら再帰呼び出し
            remove_files_recursive(fullpath, re, deleted, failed);
        } else if (S_ISREG(st.st_mode)) {
            // 通常ファイルなら正規表現で判定
            if (regex_match(filename, re)) {
                // 削除実行
                if (remove(fullpath.c_str()) == 0) {
                    cout << fullpath << " を削除しました。" << endl;
                    ++deleted;
                } else {
                    cout << fullpath << " の削除に失敗しました。" << endl;
                    ++failed;
                }
            }
        }
    }
    closedir(dir); // ディレクトリを閉じる
}

// メイン関数
int main()
{

    // ユーザーから正規表現パターンを入力してもらう
    string pattern;
    cout << "削除したいファイル名の正規表現を入力してください: ";
    getline(cin, pattern);

    regex re(pattern); // 正規表現オブジェクト作成
    int deleted = 0, failed = 0; // 削除・失敗件数カウンタ

    string current_dir = "."; // カレントディレクトリ
    remove_files_recursive(current_dir, re, deleted, failed); // 再帰的に削除処理

    // 結果を表示
    cout << "削除完了: " << deleted << "件, 失敗: " << failed << "件" << endl;
    return 0;
}