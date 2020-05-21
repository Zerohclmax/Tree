#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;


const int maxn=20;
char s[maxn];                       //保存读入结点
bool failed;
struct Node{
    bool have_value;
    int v;
    Node *left,*right;
    Node():have_value(false),left(NULL),right(NULL){}
};
Node* root;

Node* newnode(){
    return new Node;
}
void remove_tree(Node* u){
    if(u==NULL) return;
    remove_tree(u->left);
    remove_tree(u->right);
    delete u;
}
void addnode(int v,char* s){
    unsigned long n= strlen(s);
    Node* u=root;

    for (int i=0; i<n; i++) {
        if (s[i]=='L') {
            if(u->left==NULL)u->left=newnode();//左结点不存在，那就建立新结点
            u=u->left; //往左走
        }
        else if(s[i]=='R'){
            if(u->right==NULL)u->right=newnode();
            u=u->right;
        }                   //忽略其他情况，即使最后那个多余的右括号
    }
    if(u->have_value) failed=true;  //已经赋过值，表明输入有误
    u->v=v;
    u->have_value=true;         //别忘记做标记
}

//输入和主程序
bool read_input(){
    failed=false;
    remove_tree(root);
    root=newnode();                 //创建根结点
    for (; ; ) {
        if(scanf("%s",s)!=1)return false;//整个输入结束
        if(!strcmp(s, "()")) break;//读到结束标志
        int v;
        sscanf(&s[1], "%d",&v);     //读入结点值
        addnode(v,strchr(s,',')+1); //查找逗号，然后插入结点
    }
    return true;
}

//按照层次顺序遍历这棵树。此处实用队列来完成任务
bool bfs(vector<int>& ans){
    queue<Node*> q;
    ans.clear();
    q.push(root);                    //初始时只有一个根结点
    while (!q.empty()) {
        Node* u=q.front();q.pop();
        if(!u->have_value)  return false;//有结点没有被赋值过，比噢名输入有误
        ans.push_back(u->v);        //增加到输出序列尾部
        if(u->left!=NULL)q.push(u->left);//把左子结点（如果有）放到队列中
        if(u->right!=NULL)q.push(u->right);//把右子结点放进队列
    }
    return true;
}
int main(int argc, const char * argv[]) {
    while (1) {
        if(!read_input())break;
        vector<int> ans;
        if (!failed&&bfs(ans)) {
            int len=(int)ans.size();
            for(int i=0;i<len;i++)
                printf("%d%c",ans[i],i==len-1?'\n':' ');
        }
        else printf("not complete");
    }
    return 0;
}