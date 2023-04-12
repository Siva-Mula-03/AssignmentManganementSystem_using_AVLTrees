/*Assignment Management Software System*/
#include<stdbool.h>
#include <limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1024
#define ALIKE_SIZE 50
#define NAME_SIZE 50
#define ID_SIZE 25
#define ASSIGNMENT_NUM 10
#define ARR_SIZE 10
#define QUEUE_SIZE 20;

// Structure definition for Assignment Node
typedef struct Node_Alist
{
    int student_group_id;
    char status[20];
    int evaluation_marks_of_std1;
    int evaluation_marks_of_std2;
    int viva_marks_of_std1;
    int viva_marks_of_std2;
    struct Node_Alist* lchild;
    struct Node_Alist* rchild;
    struct Node_Alist* next;
    int height;
} Assignment_Node;



typedef struct Queue_tag
{
    Assignment_Node* front;
    Assignment_Node* Rear;
}Queue;

void Initialize_queue(Queue* qptr)
{
    qptr->front=NULL;
    qptr->Rear=NULL;
}

bool isQueueEmpty(Queue* qptr)
{
    bool ans;
    if(qptr->front==NULL && qptr->Rear==NULL)
    {
        ans=true;
    }
    else{
        ans=false;
    }
    return ans;
}

void insertQueue(Queue* qptr,Assignment_Node* nptr)
{
    
        nptr->next=NULL;
        if(isQueueEmpty(qptr))
        {
            qptr->front=nptr;
            qptr->Rear=nptr;
        }
        else
        {
            qptr->Rear->next=nptr;
            qptr->Rear=nptr;
        }

   
}

Assignment_Node* DeleteQueue(Queue* qptr)
{
    
   Assignment_Node* nptr;
    if(isQueueEmpty(qptr))
    {
        printf("QUEUE IS EMPTY\n");
    }
    else
    {
       nptr=qptr->front;
     
       qptr->front=qptr->front->next;
       if(qptr->front==NULL)
       {
        qptr->Rear=NULL;
       }
     
    }
    return nptr;
}


// Structure definition for Student Record
typedef struct Node_list
{
    char student_id_1[ID_SIZE];
    char student_id_2[ID_SIZE]; 
    char student_name[NAME_SIZE];
    char group_partner[NAME_SIZE];
    int group_id;
    int assignment_id;
    char assignment_name[100];
    char deadline[11];
    char status_of_assignment[20];
    int evaluation_marks_1;
    int viva_marks_1;
    int evaluation_marks_2;
    int viva_marks_2;
    bool assignment_allocated;
    bool assignment_submitted;
    bool viva_taken;
    bool assignment_evaluated;
    struct Node_list *lchild;
    struct Node_list* rchild;
    int height;
   
} student_record;
student_record* sroot=NULL;



// Structure definition for Assignment Records
typedef struct Node_tag
{
    int assignment_id;
    int height;
    char topic_name[60];
    char status1[20];
    struct Node_tag *lchild;
    struct Node_tag *rchild;
    Assignment_Node* subroot;
    
} AssignmentRecords;
AssignmentRecords*  Aroot=NULL;

//node used in question 7
typedef struct marks_list
{
    int marks;
    int corres_g_id;
    struct marks_list* next;
}marks_node;



    // Initialize Student Record variables
void initialize_SR(student_record *student)
{
    strcpy(student->student_id_1," ");
    
   strcpy(student->student_id_2," ");
    strcpy(student->student_name, " ");
    strcpy(student->group_partner, " ");
    student->group_id = 0;
   strcpy(student->deadline, " ");
    strcpy(student->status_of_assignment, " ");
    student->evaluation_marks_1 = 0;
    student->viva_marks_1 = 0;
    student->evaluation_marks_2 = 0;
    student->viva_marks_2 = 0;
   student->viva_taken=false;
   student->assignment_evaluated=false;
   student->assignment_submitted=false;
    student->lchild=NULL;
    student->rchild=NULL;
    student->assignment_allocated=false;
    student->height=1;
}
   

       // Initialize Assignment Records variables
    
    void initialize_AR( AssignmentRecords *assignment)
{
    assignment->assignment_id = 0;
    strcpy(assignment->topic_name, " ");
    strcpy(assignment->status1, " ");
    assignment->lchild = NULL;
    assignment->rchild = NULL;
    assignment->subroot=NULL;
    assignment->height=1;
    
}
    // Initialize Assignment Node variables
    void initialize_AssignNode(Assignment_Node *groups)
{
    groups->student_group_id = 0;
    strcpy(groups->status, "notsubmitted");
    groups->evaluation_marks_of_std1 = 0;
    groups->evaluation_marks_of_std2 = 0;
    groups->viva_marks_of_std1 = 0;
    groups->viva_marks_of_std2 = 0;
    groups->lchild = NULL;
    groups->rchild = NULL;
    groups->height=1;
}
int get_height( student_record *p) {
    int ans;
    int hl=0,hr=0;
    if(p && p->lchild)
    {
        hl=p->lchild->height;
    }
    if(p && p->rchild)
    {
        hr=p->rchild->height;
    }
    if(hl>hr)
    {
        ans=hl+1;
    }
    else
    {
        ans=hr+1;
    }
    return ans;
}

int get_Aheight( AssignmentRecords *p) {
    int ans;
    int hl=0,hr=0;
    if(p && p->lchild)
    {
        hl=p->lchild->height;
    }
    if(p && p->rchild)
    {
        hr=p->rchild->height;
    }
    if(hl>hr)
    {
        ans=hl+1;
    }
    else
    {
        ans=hr+1;
    }
    return ans;
}

int get_Nheight( Assignment_Node *p) {
    int ans;
    int hl=0,hr=0;
    if(p && p->lchild)
    {
        hl=p->lchild->height;
    }
    if(p && p->rchild)
    {
        hr=p->rchild->height;
    }
    if(hl>hr)
    {
        ans=hl+1;
    }
    else
    {
        ans=hr+1;
    }
    return ans;
}

int balancefactor( student_record *node)
{
    int hl=0,hr=0;
    if(node && node->lchild)
    {
        hl=node->lchild->height;
    }
    if(node && node->rchild)
    {
        hr=node->rchild->height;
    }
    return hl-hr;
}


int Assignbalancefactor( AssignmentRecords *node)
{
    int hl=0,hr=0;
    if(node && node->lchild)
    {
        hl=node->lchild->height;
    }
    if(node && node->rchild)
    {
        hr=node->rchild->height;
    }
    return hl-hr;
}

int Nodebalancefactor( Assignment_Node *node)
{
    int hl=0,hr=0;
    if(node && node->lchild)
    {
        hl=node->lchild->height;
    }
    if(node && node->rchild)
    {
        hr=node->rchild->height;
    }
    return hl-hr;
}

student_record* LLrotation( student_record *node)
{
    student_record *pl=node->lchild;
    student_record *plr=pl->rchild;
    pl->rchild=node;
    node->lchild=plr;
    node->height=get_height(node);
    pl->height=get_height(pl);
    if(node==sroot)
    {
        sroot=pl;
    }
    return pl;
}

student_record* RRrotation( student_record *node)
{
    student_record *pr=node->rchild;
    student_record *prl=pr->lchild;
    pr->lchild=node;
    node->rchild=prl;
    node->height=get_height(node);
    pr->height=get_height(pr);
    if(node==sroot)
    {
        sroot=pr;
    }
    return pr;
}

student_record* LRrotation( student_record *node)
{
    student_record *pl=node->lchild;
    student_record *plr=pl->rchild;
    pl->rchild=plr->lchild;
    node->lchild=plr->rchild;
    plr->lchild=pl;
    plr->rchild=node;
    node->height=get_height(node);
    pl->height=get_height(pl);
    plr->height=get_height(plr);
    if(node==sroot)
    {
        sroot=plr;
    }
    return plr;
}

student_record* RLrotation( student_record *node)
{
    student_record *pr=node->rchild;
    student_record *prl=pr->lchild;
    pr->lchild=prl->rchild;
    node->rchild=prl->lchild;
    prl->rchild=pr;
    prl->lchild=node;
    node->height=get_height(node);
    pr->height=get_height(pr);
    prl->height=get_height(prl);
    if(node==sroot)
    {
        sroot=prl;
    }
    return prl;
}

AssignmentRecords* ALLrotation( AssignmentRecords *node)
{
    AssignmentRecords *pl=node->lchild;
    AssignmentRecords *plr=pl->rchild;
    pl->rchild=node;
    node->lchild=plr;
    node->height=get_Aheight(node);
    pl->height=get_Aheight(pl);
    if(node==Aroot)
    {
        Aroot=pl;
    }
    return pl;
}

AssignmentRecords* ARRrotation( AssignmentRecords *node)
{
    AssignmentRecords *pr=node->rchild;
    AssignmentRecords *prl=pr->lchild;
    pr->lchild=node;
    node->rchild=prl;
    node->height=get_Aheight(node);
    pr->height=get_Aheight(pr);
    if(node==Aroot)
    {
        Aroot=pr;
    }
    return pr;
}



AssignmentRecords* ALRrotation( AssignmentRecords *node)
{
    AssignmentRecords *pl=node->lchild;
    AssignmentRecords *plr=pl->rchild;
    pl->rchild=plr->lchild;
    node->lchild=plr->rchild;
    plr->lchild=pl;
    plr->rchild=node;
    node->height=get_Aheight(node);
    pl->height=get_Aheight(pl);
    plr->height=get_Aheight(plr);
    if(node==Aroot)
    {
        Aroot=plr;
    }
    return plr;
}

AssignmentRecords* ARLrotation( AssignmentRecords *node)
{
    AssignmentRecords *pr=node->rchild;
    AssignmentRecords *prl=pr->lchild;
    pr->lchild=prl->rchild;
    node->rchild=prl->lchild;
    prl->rchild=pr;
    prl->lchild=node;
    node->height=get_Aheight(node);
    pr->height=get_Aheight(pr);
    prl->height=get_Aheight(prl);
    if(node==Aroot)
    {
        Aroot=prl;
    }
    return prl;
}

Assignment_Node* NLLrotation( Assignment_Node* Nroot,Assignment_Node *node)
{
    Assignment_Node *pl=node->lchild;
    Assignment_Node *plr=pl->rchild;
    pl->rchild=node;
    node->lchild=plr;
    node->height=get_Nheight(node);
    pl->height=get_Nheight(pl);
    if(node==Nroot)
    {
        Nroot=pl;
    }
    return pl;
}

Assignment_Node* NRRrotation( Assignment_Node* Nroot,Assignment_Node *node)
{
    Assignment_Node *pr=node->rchild;
    Assignment_Node *prl=pr->lchild;
    pr->lchild=node;
    node->rchild=prl;
    node->height=get_Nheight(node);
    pr->height=get_Nheight(pr);
    if(node==Nroot)
    {
        Nroot=pr;
    }
    return pr;
}



Assignment_Node* NLRrotation(Assignment_Node* Nroot,Assignment_Node *node)
{

Assignment_Node* pl=node->lchild;
Assignment_Node* plr=pl->rchild;
pl->rchild=plr->lchild;
node->lchild=plr->rchild;
plr->lchild=pl;
plr->rchild=node;
node->height=get_Nheight(node);
pl->height=get_Nheight(pl);
     plr->height=get_Nheight(plr);
     if(node==Nroot)
    {
        Nroot=plr;
    }
     return plr;
}


Assignment_Node* NRLrotation(Assignment_Node* Nroot,Assignment_Node *node)
{
 Assignment_Node *pr=node->rchild;
    Assignment_Node *prl=pr->lchild;
    pr->lchild=prl->rchild;
    node->rchild=prl->lchild;
    prl->rchild=pr;
    prl->lchild=node;
    node->height=get_Nheight(node);
    pr->height=get_Nheight(pr);
    prl->height=get_Nheight(prl);
    if(node==Nroot)
    {
        Nroot=prl;
    }
    return prl;
}

student_record* addstree(student_record* ptr,student_record* temp,int key)
{
    
   
    if(ptr==NULL)
    {
        char Curr_s[20]="submitted";
      student_record* newnode= (student_record*) malloc(sizeof(student_record)); 
      initialize_SR(newnode);
      newnode->group_id=key;
      newnode->assignment_id=temp->assignment_id;
      if(temp->assignment_id > 0)
      {
        newnode->assignment_allocated=true;
      }
      else 
      {
        newnode->assignment_allocated=false;
      }
        strcpy(newnode->student_id_1,temp->student_id_1);
        strcpy(newnode->student_id_2,temp->student_id_2);
        strcpy(newnode->student_name,temp->student_name);
        strcpy(newnode->group_partner,temp->group_partner);
        if(newnode->assignment_allocated==true)
        {
        strcpy(newnode->assignment_name,temp->assignment_name);
        strcpy(newnode->deadline,temp->deadline);
        strcpy(newnode->status_of_assignment,temp->status_of_assignment);
        
        newnode->evaluation_marks_1=temp->evaluation_marks_1;
        newnode->viva_marks_1=temp->viva_marks_1;
        newnode->evaluation_marks_2=temp->evaluation_marks_2;
        newnode->viva_marks_2=temp->viva_marks_2;
        if(strcmp(newnode->status_of_assignment,Curr_s)==0)
        {
            newnode->assignment_submitted=true;
        if(newnode->viva_marks_1>0 || newnode->viva_marks_2>0)
        {
            newnode->viva_taken=true;
        }
        else
        {
            newnode->viva_taken=false;
        }
        if(newnode->evaluation_marks_1>0 || newnode->evaluation_marks_2>0)
        {
          newnode->assignment_evaluated=true;
          strcpy(newnode->status_of_assignment,"submitted");
        }
        else
        {
            newnode->assignment_evaluated=false;
        }

        }
        
      
        }
        
        newnode->lchild=NULL;
        newnode->rchild=NULL;
        newnode->height=1;
        return newnode;

    }
    if(ptr->group_id==key)
    {
        printf("Duplicate key");
    }
    else if(ptr->group_id<key)
    {
        ptr->rchild=addstree(ptr->rchild,temp,key);
    }
    else if(ptr->group_id>key)
    {
        ptr->lchild=addstree(ptr->lchild,temp,key);
    }
    
    ptr->height=get_height(ptr);


    if(balancefactor(ptr)==2 && balancefactor(ptr->lchild)==1)
    {
        return LLrotation(ptr);
    }
    else if(balancefactor(ptr)==2 && balancefactor(ptr->lchild)==-1)
    {
        return LRrotation(ptr);
    }
    else if(balancefactor(ptr)==-2 && balancefactor(ptr->rchild)==-1)
    {
        return RRrotation(ptr);
    }
    else if(balancefactor(ptr)==-2 && balancefactor(ptr->rchild)==1)
    {
        return RLrotation(ptr);
    }

    return ptr;
    
   
  
   
  
}

//function addatree


AssignmentRecords* addatree(AssignmentRecords* ptr,AssignmentRecords* temp,int key)
{
    
   
    if(ptr==NULL)
    {
      AssignmentRecords* newnode= (AssignmentRecords*) malloc(sizeof(AssignmentRecords)); 
      initialize_AR(newnode);
      newnode->assignment_id=key;
      strcpy(newnode->topic_name,temp->topic_name);
        strcpy(newnode->status1,temp->status1);
        newnode->lchild=NULL;
        newnode->rchild=NULL;
        newnode->height=1;
        return newnode;

    }
    if(ptr->assignment_id==key)
    {
        printf("Duplicate key");
    }
    else if(ptr->assignment_id<key)
    {
        ptr->rchild=addatree(ptr->rchild,temp,key);
    }
    else if(ptr->assignment_id>key)
    {
        ptr->lchild=addatree(ptr->lchild,temp,key);
    }
    
    ptr->height=get_Aheight(ptr);

    if(Assignbalancefactor(ptr)==2 && Assignbalancefactor(ptr->lchild)==1)
    {
        return ALLrotation(ptr);
    }
    else if(Assignbalancefactor(ptr)==2 && Assignbalancefactor(ptr->lchild)==-1)
    {
        return ALRrotation(ptr);
    }
    else if(Assignbalancefactor(ptr)==-2 && Assignbalancefactor(ptr->rchild)==-1)
    {
        return ARRrotation(ptr);
    }
    else if(Assignbalancefactor(ptr)==-2 && Assignbalancefactor(ptr->rchild)==1)
    {
        return ARLrotation(ptr);
    }

    return ptr;

}

Assignment_Node* addSubtree(Assignment_Node* Troot,Assignment_Node* temp,student_record* ptr)
{
  
    if(temp==NULL)
    {
        Assignment_Node* newnode= (Assignment_Node*) malloc(sizeof(Assignment_Node));
        initialize_AssignNode(newnode);
        newnode->student_group_id=ptr->group_id;
        newnode->evaluation_marks_of_std1=ptr->evaluation_marks_1;
        newnode->viva_marks_of_std1=ptr->viva_marks_1;
        newnode->evaluation_marks_of_std2=ptr->evaluation_marks_2;
        newnode->viva_marks_of_std2=ptr->viva_marks_2;
        strcpy(newnode->status,ptr->status_of_assignment);
        newnode->height=1;
        return newnode;
    }
    if(temp->student_group_id==ptr->group_id)
    {
        printf("Duplicate key");
    }
    else if(temp->student_group_id<ptr->group_id)
    {
        temp->rchild=addSubtree(Troot,temp->rchild,ptr);
    }
    else if(temp->student_group_id>ptr->group_id)
    {
        temp->lchild=addSubtree(Troot,temp->lchild,ptr);
    }
   
   temp->height=get_Nheight(temp);

   if(Nodebalancefactor(temp)==2 && Nodebalancefactor(temp->lchild)==1)
    {
        return NLLrotation(Troot,temp);
    }
    else if(Nodebalancefactor(temp)==2 && Nodebalancefactor(temp->lchild)==-1)
    {
        return NLRrotation(Troot,temp);
    }
    else if(Nodebalancefactor(temp)==-2 && Nodebalancefactor(temp->rchild)==-1)
    {
        return NRRrotation(Troot,temp);
    }
    else if(Nodebalancefactor(temp)==-2 && Nodebalancefactor(temp->rchild)==1)
    {
        return NRLrotation(Troot,temp);
    }
  return temp;
}
//function to create student database
void create_Student_record( )
{
    FILE* fp = fopen("evaluation1.csv", "r");
      student_record* strav=(student_record*) malloc(sizeof(student_record));
     student_record* Sptr;
      
    if (!fp)
        printf("Can't open file\n");
 
    else {
        
        char buffer[MAX_SIZE];
        int key1=0;
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,
                     MAX_SIZE, fp)) {
            column = 0;
            row++;
          if(row==1)
          {
            //skip this iteration
          }
          else
          {
            
            char* value = strtok(buffer, ", ");
 
            while (value) {
                
                if (column == 0) {
                   strav->group_id=atoi(value);
                   key1=strav->group_id;
                }
 
                if (column == 1) {
                    strcpy(strav->student_id_1,value);
                }
 
               
                if (column == 2) {
                   strcpy(strav->student_id_2,value);
                }
                 
                 if (column == 3) {
                    strcpy(strav->student_name,value);
                }

                if (column == 4) {
                   strcpy(strav->group_partner,value);
                }

                if (column == 5) {
                   strav->assignment_id=atoi(value);
                   

                }

                if (column == 6) {
                   strcpy(strav->assignment_name,value);
                }

                if (column == 7) {
                   strcpy(strav->deadline,value);
                }

                if (column == 8) {
                   strcpy(strav->status_of_assignment,value);
                }

                 if (column == 9) {
                   strav->evaluation_marks_1=atoi(value);
                }
                
                 if (column == 10) {
                  strav->viva_marks_1=atoi(value);
                }

                 if (column == 11) {
                  strav->evaluation_marks_2=atoi(value);
                }
                
                if (column == 12) {
                  strav->viva_marks_2=atoi(value);
                }

                value = strtok(NULL, ", ");
                column++;
            }
         //printf("%d\n",key1); 
         sroot= addstree(sroot,strav,key1);
        
         initialize_SR(strav);  
           }   
        }
 
       
      fclose(fp);
    }
    
}

//function to create assignment database

void create_Assignment_record( )
{
    FILE* fp = fopen("assignmentRecord.csv", "r");
      AssignmentRecords* astrav=(AssignmentRecords*) malloc(sizeof(AssignmentRecords));
        AssignmentRecords* Aptr;

    if (!fp)
        printf("Can't open file\n");
 
    else {
        
        char buffer[MAX_SIZE];
        int key1=0;
        int row = 0;
        int column = 0;
 
        while (fgets(buffer,
                     MAX_SIZE, fp)) {
            column = 0;
            row++;
          if(row==1)
          {
            //skip this iteration
          }
          else
          {
          
            char* value = strtok(buffer, ", ");
 
            while (value) {
                
                if (column == 0) {
                   astrav->assignment_id=atoi(value);
                   key1=astrav->assignment_id;
                }
 
                if (column == 1) {
                    strcpy(astrav->topic_name,value);
                }
 
               
                if (column == 2) {
                   strcpy(astrav->status1,value);
                }
                 
                

                value = strtok(NULL, ", ");
                column++;
            }
           
         Aroot= addatree(Aroot,astrav,key1);
           
           }   
        }
 
       
      fclose(fp);
    }


}
AssignmentRecords* Rsearch(AssignmentRecords* t,int key)
{
   
    if(t==NULL)
    {
       return NULL;
    }
  
        if(t->assignment_id==key)
        {
            return t;
        }
        else if(t->assignment_id<key)
        {
            return Rsearch(t->rchild,key);
        }
        else if(t->assignment_id>key)
        {
            return Rsearch(t->lchild,key);
        }
   
}

student_record* Stud_search(student_record* t,int key)
{ 
    
    if(t==NULL)
    {
       return NULL;
    }
  
        if(t->group_id==key)
        {
            return t;
        }
        else if(t->group_id<key)
        {
            return Stud_search(t->rchild,key);
        }
        else if(t->group_id>key)
        {
            return Stud_search(t->lchild,key);
        }
}

Assignment_Node* Subsearch(Assignment_Node*t,int key)
{
    if(t==NULL)
    {
        return NULL;
    }

    if(t->student_group_id==key)
    {
        return t;
    }
    else if(t->student_group_id<key)
    {
        return Subsearch(t->rchild,key);
    }
    else if(t->student_group_id>key)
    {
        return Subsearch(t->lchild,key);
    }


}


void createSubtree(student_record* sptr)
{
    int key;
    AssignmentRecords* temp=NULL;
     if(sptr!=NULL)
     {
       
        createSubtree(sptr->lchild);
        key=sptr->assignment_id;
        temp=Rsearch(Aroot,key);
        temp->subroot=addSubtree(temp->subroot,temp->subroot,sptr);
        createSubtree(sptr->rchild);
     }

}

void Sinorder(student_record* ptr)
{
    
  
    if(ptr!=NULL)
    {
        Sinorder(ptr->lchild);
        printf("\n");
        printf("GROUP ID : %d \n ",ptr->group_id);
        printf("STUDENT ID 1 : %s \n ",ptr->student_id_1);
        printf("STUDENT ID 2 : %s \n ",ptr->student_id_2);
        printf("STUDENT NAME : %s \n ",ptr->student_name);
        printf("GROUP PARTNER : %s \n ",ptr->group_partner);
        printf("ASSIGNMENT ID : %d \n ",ptr->assignment_id);
        printf("ASSIGNMENT NAME : %s \n ",ptr->assignment_name);
        printf("DEADLINE : %s \n ",ptr->deadline);
        printf("STATUS OF ASSIGNMENT : %s \n ",ptr->status_of_assignment);
        printf("EVALUATION MARKS 1 : %d \n ",ptr->evaluation_marks_1);
        printf("VIVA MARKS 1 : %d \n ",ptr->viva_marks_1);
        printf("EVALUATION MARKS 2 : %d \n ",ptr->evaluation_marks_2);
        printf("VIVA MARKS 2 : %d \n ",ptr->viva_marks_2);
        // printf("ASSIGNMENT SUBMITTED : %d \n ",ptr->assignment_submitted);
        // printf("VIVA TAKEN : %d \n ",ptr->viva_taken);
        // printf("ASSIGNMENT EVALUATED : %d \n ",ptr->assignment_evaluated);
        printf("\n");
        Sinorder(ptr->rchild);
    }
}

void Subinorder(Assignment_Node* nodeptr)
{

    if(nodeptr!=NULL)
    {
        Subinorder(nodeptr->lchild);
        printf("\n");
        printf("GROUP ID : %d \n ",nodeptr->student_group_id);
         printf("EVALUATION MARKS 1 : %d \n ",nodeptr->evaluation_marks_of_std1);
        printf("VIVA MARKS 1 : %d \n ",nodeptr->evaluation_marks_of_std2);
        printf("EVALUATION MARKS 2 : %d \n ",nodeptr->viva_marks_of_std1);
        printf("VIVA MARKS 2 : %d \n ",nodeptr->viva_marks_of_std2);
        printf("STATUS OF THE ASSIGNMENT : %s \n",nodeptr->status);
        printf("\n");
        Subinorder(nodeptr->rchild);
    }
    printf("\n");
}
void Ainorder(AssignmentRecords* ptr)
{
    
   
    if(ptr!=NULL)
    {
        Ainorder(ptr->lchild);
        printf("ASSIGNMENT ID : %d \n ",ptr->assignment_id);
        printf("ASSIGNMENT NAME : %s \n ",ptr->topic_name);
        printf("STATUS OF ASSIGNMENT : %s \n ",ptr->status1);
        printf("\t INNER DATABASE \t \n");
        Subinorder(ptr->subroot);
        Ainorder(ptr->rchild);
    }
}


//question 1
void insertStudentRecord()
{

   char submission_date[11];
    AssignmentRecords* lptr;
    student_record* strav;
    
    AssignmentRecords* temp;
    int em1,em2,vm1,vm2;
    char Aname[60];
   char Astatus[20]="declared";
    int gid;
    int assignid;
    char st[20];
    char Curr_stat[20]="submitted";
    char name1[NAME_SIZE];
    char name2[NAME_SIZE];
    char id1[ID_SIZE];
    char id2[ID_SIZE];
    char assign_name[100];
    int assign_id;
    char Dline[11];
        printf("ENTER THE GROUP ID THAT HAS TO BE INSERTED \n");
        scanf("%d",&gid);
        strav=Stud_search(sroot,gid);
        if(!strav)
        {
        printf("GROUP DOSENT EXIST IN THE DATABASE \n");
        student_record* nptr=(student_record*)malloc(sizeof(student_record));
        initialize_SR(nptr);
        printf("ENTER THE NAME OF STUDENT 1:\t");
    	scanf("%s",name1);
        printf("ENTER THE NAME OF STUDENT 2 : \t");
        scanf("%s",name2);
        printf("ENTER THE STUDENT ID 1 \t");
        scanf("%s",id1);
        printf("ENTER THE STUDENT ID 2 \t");
        scanf("%s",id2);
        printf("ENTER THE ASSIGNMENT ID \t \t");
        scanf("%d",&assign_id);
        if(assign_id>0)
        {
            nptr->assignment_allocated=true;
       printf("ENTER THE ASSIGNMENT NAME THAT HAS TO BE ALLOCATED \t ");
        scanf("%s",assign_name);
        printf("ENTER THE STATUS OF THE ASSIGNMENT \t");
        scanf("%s",st);
        printf("ENTER THE DEADLINE OF THE ASSIGNMENT \t ");
        scanf("%s",Dline);
        strcpy(nptr->student_id_1,id1);
        strcpy(nptr->student_id_2,id2);
        strcpy(nptr->assignment_name,assign_name);
        strcpy(nptr->student_name,name1);
        strcpy(nptr->group_partner,name2);
        strcpy(nptr->deadline,Dline);
        strcpy(nptr->status_of_assignment,st);
        if(strcmp(nptr->status_of_assignment,Curr_stat)==0)
        {

            nptr->assignment_submitted=true;
            printf("ENTER THE EVAL MARKS 1\t");
            scanf("%d",&em1);
             printf("ENTER THE EVAL MARKS 2\t");
            scanf("%d",&em2);
             printf("ENTER THE VIVA MARKS 1\t");
            scanf("%d",&vm1);
             printf("ENTER THE VIVA MARKS 1\t");
            scanf("%d",&vm2);
            nptr->evaluation_marks_1=em1;
            nptr->evaluation_marks_2=em2;
            nptr->viva_marks_1=vm1;
            nptr->viva_marks_2=vm2;
            if(em1>0||em2>0)
            {
                nptr->assignment_evaluated=true;
                strcpy(nptr->status_of_assignment,"evaluated");
            }
            if(vm1>0||vm2>0)
            {
                nptr->viva_taken=true;
            }
           
        }

        }

       nptr->assignment_id=assign_id;
        nptr->group_id=gid;
        //adding the node to student record
       sroot=addstree(sroot,nptr,gid);
       
     temp=Rsearch(Aroot,assign_id);
     if(!temp)
     {
        printf("ASSIGNMENT RECORD OF THAT ASSIGNMENT DOSENT EXIST SO HAVE TO INSERT THAT ASSIGNMENT RECORD \n");
       AssignmentRecords* newptr=(AssignmentRecords*)malloc(sizeof(AssignmentRecords));
        initialize_AR(newptr);
        newptr->assignment_id=assign_id;
        strcpy(newptr->topic_name,assign_name);
        strcpy(newptr->status1,Astatus);
        Aroot=addatree(Aroot,newptr,assign_id);
       lptr=Rsearch(Aroot,assign_id);
        lptr->subroot=addSubtree(lptr->subroot,lptr->subroot,nptr);
     }  
    else
    {
        //that assignment record exist 
        //then add this group to corresponding subtree
        //have to do changes
        strcpy(temp->topic_name,assign_name);
        strcpy(temp->status1,Astatus);
        temp->subroot=addSubtree(temp->subroot,temp->subroot,nptr);
    } 















       
        }
        else
        {
            //update the already present student record
            printf("STUDENT RECORD ALREADY EXISTS \n");


            
        }

       
       


}

//question 2
void insertAssignRecord()
{
    AssignmentRecords* atraverse;
    student_record* strav;
    char st[20]="notsubmitted";
    char name1[NAME_SIZE];
    char name2[NAME_SIZE];
    char id1[ID_SIZE];
    char id2[ID_SIZE];
    char assign_name[100];
    int assign_id;
    char Dline[11];
    student_record* temporary;
    student_record* lpptr;
    int groupID;
    int no_of_groups;
    int i=1;
    AssignmentRecords* temp;
    int Aid;
   char Aname[60];
   char Astatus[20]="declared";
   printf("ENTER THE ASSIGNMENT ID :\t ");
   scanf("%d",&Aid);
  temp=Rsearch(Aroot,Aid);
  if(!temp)
  {
    printf("ASSIGNMENT RECORD DOSENT EXIST HAVE TO INSERT THAT ASSIGNMENT RECORD \n");
   AssignmentRecords* nptr=(AssignmentRecords*)malloc(sizeof(AssignmentRecords));
    initialize_AR(nptr);
    printf("ENTER THE TOPIC NAME \t");
   scanf("%s",Aname);
   strcpy(nptr->topic_name,Aname);
    strcpy(nptr->status1,Astatus);
    nptr->assignment_id=Aid;
    Aroot=addatree(Aroot,nptr,Aid);
  }
  else
  {
    //it exists already update it 
    strcpy(temp->topic_name,Aname);
    strcpy(temp->status1,Astatus);
  }
  //now we have to allocate this assignment to multiple student groups
  //if the student group exists then allocate this assignment to that group if that group was not allocated with any assignment
  //if that group was actually allocated with any assignment then dont select that group 
  //if you allocate assignment to a student group who dosent exist in the student record database then we have to insert that student group in student database

   printf("Enter the no of groups to which assignment %d  have to be allocated \t",Aid);
    scanf("%d",&no_of_groups);
  while(i<=no_of_groups)
  {
    printf("ENTER THE GROUP ID : \n");
    scanf("%d",&groupID);
    temporary=Stud_search(sroot,groupID);
    if(!temporary)
    {
        printf("STUDENT RECORD DOSENT EXIST\n");
        //create new node and add it
        lpptr=(student_record*)malloc(sizeof(student_record));
        initialize_SR(lpptr);
        lpptr->group_id=groupID;
       lpptr->assignment_id=Aid;
        printf("ENTER THE NAME OF STUDENT 1:\t");
    	scanf("%s",name1);
        printf("ENTER THE NAME OF STUDENT 2 : \t");
        scanf("%s",name2);
        printf("ENTER THE STUDENT ID 1 \t");
        scanf("%s",id1);
        printf("ENTER THE STUDENT ID 2 \t");
        scanf("%s",id2);
        printf("ENTER THE DEADLINE OF THE ASSIGNMENT \t ");
        scanf("%s",Dline);
        strcpy(lpptr->student_id_1,id1);
        strcpy(lpptr->student_id_2,id2);
        strcpy(lpptr->assignment_name,Aname);
        strcpy(lpptr->student_name,name1);
        strcpy(lpptr->group_partner,name2);
        strcpy(lpptr->deadline,Dline);
        strcpy(lpptr->status_of_assignment,st);
        
        sroot=addstree(sroot,lpptr,groupID);
        strav=Stud_search(sroot,groupID);
        //HAVE TO UPDATE INNER DATABASE AS WELL
        atraverse=Rsearch(Aroot,Aid);
        atraverse->subroot=addSubtree(atraverse->subroot,atraverse->subroot,strav);

        i++;

    }
    else
    {
        if(temporary->assignment_allocated==true)
        {
            //if assignment was already allocated to a group then skip this iteration
            //continue;
            printf("GROUP WAS ALREADY ALLOCATED WITH ASSIGNMENT SO PLEASE ENTER NEW GROUP ID \n");
        }
        else
        {
            //if assignment was not previously allocated to a group then allocate it
            temporary->assignment_id=Aid;
            strcpy(temporary->assignment_name,Aname);
            strcpy(temporary->status_of_assignment,st);
            strcpy(temporary->deadline,Dline);
            strav=Stud_search(sroot,groupID);
            atraverse=Rsearch(Aroot,Aid);
            atraverse->subroot=addSubtree(atraverse->subroot,atraverse->subroot,strav);
            i++;
        }
    }
  }


}

//question 3a
void submittingAssignments(student_record* ptr)
{
     char submission_date[11];
     student_record* straverse;
     AssignmentRecords* atraverse;
     Assignment_Node* apptr;
     if(ptr!=NULL)
     {
        submittingAssignments(ptr->lchild);

        if(ptr->assignment_submitted)
        {
            printf(" Submission for group with GROUP ID %d already recorded.\n",ptr->group_id);
        }
        else
        {
        printf("ENTER THE DATE IN THE YEAR-MONTH-DAY FORMAT\n");
        printf("ENTER THE SUBMISSION DATE OF GROUP %d\n",ptr->group_id);
        scanf("%s",submission_date);
            if(strcmp(submission_date,ptr->deadline)<=0)
            {
                strcpy(ptr->status_of_assignment,"submitted");
                ptr->assignment_submitted=true;
            }
            else
            {
                 printf(" Submission for group with GROUP ID %d WAS LATE!.\n", ptr->group_id);

            }
        }
       atraverse=Rsearch(Aroot,ptr->assignment_id);
       apptr=Subsearch(atraverse->subroot,ptr->group_id);
       //change the status of the internal node correspondingly
       strcpy(apptr->status,ptr->status_of_assignment);


       submittingAssignments(ptr->rchild);


        

     }

}

// bool checkingStatus(Assignment_Node* ptr)
// {
//     printf("HI");
//     Queue q;
//     int flag=1;
//     bool ans;
//     Assignment_Node* p;
   
//     bool ans2;
//      char sttt[20]="evaluated";
//     insertQueue(&q,ptr);
//     while(!isQueueEmpty(&q)&& flag==1)
//     {
//         p=DeleteQueue(&q);
//         if(strcmp(p->status,sttt)!=0)
//         {
//            flag=0; 
//         }
//         else
//         {
//         if(p->lchild!=NULL)
//         {
//                 insertQueue(&q,p->lchild);
            
//         }
       
//             if(p->rchild!=NULL)
//         {
           
//                 insertQueue(&q,p->rchild);
            
//         }
        

//         }
       

//     }
//     if(flag==1)
//     {
//        ans=true;
//     }
//     else
//     {
//         ans=false;
//     }
//     return ans;
// }

int numNodes=0;
char stasta[20]="evaluated";
int countNodes(Assignment_Node* ptr)
{
    int x=0,y=0,ans;
    if(ptr!=NULL)
    {
        if(strcmp(ptr->status,stasta)==0)
        {
            numNodes++;
        }
        x=countNodes(ptr->lchild);
        y=countNodes(ptr->rchild);
        ans=x+y+1;
    }
    else
    {
        ans=x+y;
    }
    return ans;
}




//question 3b
void evaluating_assignments(student_record* ptr)
{
   AssignmentRecords* atrav;
   Assignment_Node* subtrav;
    int em1,em2,vm1,vm2;
    int x;
    if(ptr!=NULL)
    {
        evaluating_assignments(ptr->lchild);
        if(ptr->assignment_submitted)
        {
            if(ptr->assignment_evaluated)
            {
                 printf("Assignment was already Evaluated \n");
            }
            else
            {
                printf("ENTER THE VALUE AS 1 TO EVALUATE THE ASSIGNMENT \t");
                scanf("%d",&x);
                if(x==1)
                {
                printf("ENTER THE EVALUATION MARKS 1 \t");
                scanf("%d",&em1);
                printf("ENTER THE VIVA MARKS 1 \t");
                scanf("%d",&em2);
                printf("ENTER THE EVALUATION MARKS 2 \t");
                scanf("%d",&vm1);
                printf("ENTER THE VIVA MARKS 2 \t");
                scanf("%d",&vm2);
                ptr->evaluation_marks_1=em1;
                ptr->viva_marks_1=vm1;
                ptr->evaluation_marks_2=em2;
                ptr->viva_marks_2=vm2;
                strcpy(ptr->status_of_assignment,"evaluated");
                ptr->viva_taken=true;
                atrav=Rsearch(Aroot,ptr->assignment_id);
                subtrav=Subsearch(atrav->subroot,ptr->group_id);
                //update marks of subtrav
                subtrav->evaluation_marks_of_std1=em1;
                subtrav->evaluation_marks_of_std2=em2;
                subtrav->viva_marks_of_std1=vm1;
                subtrav->viva_marks_of_std2=vm2;
                strcpy(subtrav->status,"evaluated");
                
                ptr->assignment_evaluated=true;
                }
                else
                {
                    ptr->assignment_evaluated=false;
                    ptr->viva_taken=false;
                }
                

            }
        }
        

        evaluating_assignments(ptr->rchild);
    }
     
}

// void change_assign_status(AssignmentRecords* aptr)
// {
//     bool ans;
//        if(aptr!=NULL)
//        {
//         change_assign_status(aptr->lchild);
        
//         ans=checkingStatus(aptr->subroot);
//         if(ans)
//         {
//             strcpy(aptr->status1,"evaluated");
//         }
//         else
//         {
            
//         }

//         change_assign_status(aptr->rchild);
//        }
// }


void change_assign_status(AssignmentRecords* aptr)
{
    int y;
    
       if(aptr!=NULL)
       {
        change_assign_status(aptr->lchild);
        y=countNodes(aptr->subroot);
        if(numNodes==y && y!=0 && numNodes!=0 )
        {
            strcpy(aptr->status1,"evaluated");
        }
        numNodes=0;

        change_assign_status(aptr->rchild);
       }
}









//question 4
void changeassignments(AssignmentRecords* ptr)
{
    char str[20]="declared";
    if(ptr!=NULL)
    {
        changeassignments(ptr->lchild);
        if(strcmp(ptr->status1,str)==0)
        {
            printf("ASSIGNMENT ID -%d/t \n",ptr->assignment_id);
            printf("ASSIGNMENT NAME -%s/t/n",ptr->topic_name);
        }
    
        changeassignments(ptr->rchild);
    }

}

//QUESTION 5
void printDueStudentgroups(student_record* ptr)
{
   char submission_date[11];
   if(ptr!=NULL)
   {
    printDueStudentgroups(ptr->lchild);
      if(ptr->assignment_submitted)
        {
            printf(" Submission for group with GROUP ID %d already recorded.\n",ptr->group_id);
        }
        else
        {
        printf("ENTER THE DATE IN THE YEAR-MONTH-DAY FORMAT\n");
        printf("ENTER THE SUBMISSION DATE OF GROUP %d\n",ptr->group_id);
        scanf("%s",submission_date);
            if(strcmp(submission_date,ptr->deadline)<=0)
            {
                strcpy(ptr->status_of_assignment,"submitted");
                ptr->assignment_submitted=true;
            }
            else
            {
                 printf(" Submission for group with GROUP ID %d WAS LATE!.\n", ptr->group_id);
                 printf("GROUP ID : %d \n ",ptr->group_id);
                 printf("STUDENT ID 1 : %s \n ",ptr->student_id_1);
                 printf("STUDENT ID 2 : %s \n ",ptr->student_id_2);
                 printf("STUDENT NAME : %s \n ",ptr->student_name);
                 printf("GROUP PARTNER : %s \n ",ptr->group_partner);
                 printf("ASSIGNMENT ID : %d \n ",ptr->assignment_id);
                 printf("ASSIGNMENT NAME : %s \n ",ptr->assignment_name);
                 printf("DEADLINE : %s \n ",ptr->deadline);
                 printf("STATUS OF ASSIGNMENT : %s \n ",ptr->status_of_assignment);
                 
            }
        }
      printDueStudentgroups(ptr->rchild);  
   }

}

//question 6
void printEvalStudentGroups(student_record* ptr)
{
    
    if(ptr!=NULL)
    {
        printEvalStudentGroups(ptr->lchild);
        if(ptr->assignment_submitted)
        {
            if(!ptr->assignment_evaluated)
            {
                if(!ptr->viva_taken)
                {
                    printf("ASSIGNMENT SUBMITTED , NOT EVALUATED AND VIVA NOT TAKEN\t\n");
                     printf("GROUP ID : %d \n ",ptr->group_id);
                 printf("STUDENT ID 1 : %s \n ",ptr->student_id_1);
                 printf("STUDENT ID 2 : %s \n ",ptr->student_id_2);
                 printf("STUDENT NAME : %s \n ",ptr->student_name);
                 printf("GROUP PARTNER : %s \n ",ptr->group_partner);
                 printf("ASSIGNMENT ID : %d \n ",ptr->assignment_id);
                 printf("ASSIGNMENT NAME : %s \n ",ptr->assignment_name);
                }
                else
                {
                    printf("ASSIGNMENT SUBMITTED , NOT EVALUATED BUT VIVA WAS COMPLETED\t\n");
                     printf("GROUP ID : %d \n ",ptr->group_id);
                 printf("STUDENT ID 1 : %s \n ",ptr->student_id_1);
                 printf("STUDENT ID 2 : %s \n ",ptr->student_id_2);
                 printf("STUDENT NAME : %s \n ",ptr->student_name);
                 printf("GROUP PARTNER : %s \n ",ptr->group_partner);
                 printf("ASSIGNMENT ID : %d \n ",ptr->assignment_id);
                 printf("ASSIGNMENT NAME : %s \n ",ptr->assignment_name);

                }
            }
        }
        
        printEvalStudentGroups(ptr->rchild);
    }
}

 marks_node* head=NULL;

void subtreetraverse(Assignment_Node* nptr)
{
      
    int x;
    marks_node* mnode;
    marks_node* q,*p;
    
    int total_marks;
    if(nptr!=NULL)
    {
       subtreetraverse(nptr->lchild);
     
     total_marks=nptr->evaluation_marks_of_std1 + nptr->evaluation_marks_of_std2 + nptr->viva_marks_of_std1 + nptr->viva_marks_of_std2;
     mnode=(marks_node*)malloc(sizeof(marks_node));
            mnode->marks=total_marks;
            mnode->corres_g_id=nptr->student_group_id;
            mnode->next=NULL;
            x=total_marks;
       if(head==NULL)
       {
        head=mnode;
        p=head;
       }
       else
       {
        p=head;
            while(p && p->marks>x)
                {
                    q=p;
                    p=p->next;
                }
            if(p==head)
            {
                 mnode->next=head;
                    head=mnode;
                    p=head;
            }
            else
            {
                mnode->next=q->next;
                q->next=mnode;
            }
       }

       subtreetraverse(nptr->rchild);
    }
}
//QUESTION 7

void Assigntraverse(AssignmentRecords* ptr)
{
     student_record* sptr;
    marks_node* mtraverse;
    
    
    if(ptr!=NULL)
    {
        
        Assigntraverse(ptr->lchild);
         
       subtreetraverse(ptr->subroot);
       
       mtraverse=head;
       
       while(mtraverse!=NULL)
       {
       
         sptr=Stud_search(sroot,mtraverse->corres_g_id);
                printf("\n");
                printf("MARKS :-%d\n",mtraverse->marks);
                 printf("GROUP ID : %d \n ",sptr->group_id);
                 printf("STUDENT ID 1 : %s \n ",sptr->student_id_1);
                 printf("STUDENT ID 2 : %s \n ",sptr->student_id_2);
                 printf("STUDENT NAME : %s \n ",sptr->student_name);
                 printf("GROUP PARTNER : %s \n ",sptr->group_partner);
                 printf("ASSIGNMENT ID : %d \n ",sptr->assignment_id);
                 printf("ASSIGNMENT NAME : %s \n ",sptr->assignment_name);
                 printf("\n");
        mtraverse=mtraverse->next;
       }
       //after usage delete the marks list linked list
    
      while(head!=NULL)
      {
         mtraverse=head;
          head=head->next;
        free(mtraverse);
      }
       //head=NULL;
     
        Assigntraverse(ptr->rchild);
    }
}



int max_marks=INT_MIN;
int max_g_id;
int arr[ARR_SIZE];
int i=0;
int count;

void highestMarks(Assignment_Node* lptr)
{
    int total_marks;
    if(lptr!=NULL)
    {
       highestMarks(lptr->lchild);
        total_marks=lptr->evaluation_marks_of_std1+lptr->evaluation_marks_of_std2+lptr->viva_marks_of_std1+lptr->viva_marks_of_std2;
        if(total_marks>max_marks)
        {
            max_marks=total_marks;
           max_g_id=lptr->student_group_id;
           arr[0]=max_g_id;
        }
       else if(total_marks==max_marks)
       {
        arr[++i]=max_g_id;
        count=i;
       }

       highestMarks(lptr->rchild);
    }
}







//question 8
void corresAssign(AssignmentRecords* ptr)
{
    int j=0;
    if(ptr!=NULL)
    {
        corresAssign(ptr->lchild);
        
         highestMarks(ptr->subroot);
         
         while(j<=count)
           {
              if(arr[j]!=0)
              {
                  printf("ASSIGNMENT ID -%d\n",ptr->assignment_id);
                  printf("GROUP - %d \n",arr[j]);
              }
              else
              { 
                printf("ASSIGNMENT ID -%d\n",ptr->assignment_id);
                printf("NO GROUP WAS ALLOCATED WITH THIS ASSIGNEMNT\n");

                  
              }
              
               j++;
           }
          for(int k=0;k<ARR_SIZE;k++)
            {
               arr[k]=0;
            }
            i=0;
            max_g_id=0;
            max_marks=INT_MIN;

        corresAssign(ptr->rchild);
    }
}

//question 9
//range search
void rangesearch(AssignmentRecords* ptr,int min_val,int max_val)
{
    if(ptr!=NULL)
    {
        rangesearch(ptr->lchild,min_val,max_val);
        if(ptr->assignment_id>min_val && ptr->assignment_id< max_val)
        {
            printf("\n");
          printf("ASSIGNMENT ID -%d \n",ptr->assignment_id);
            printf("ASSIGNMENT NAME -%s\n",ptr->topic_name);
            printf("\n");
        }
        
        rangesearch(ptr->rchild,min_val,max_val);
    }
}


int main()
{
create_Student_record();
Sinorder(sroot);
create_Assignment_record();
createSubtree(sroot);
printf("\t \t \t ASSIGNMENT RECORDS \t \t\n");
Ainorder(Aroot);
 

int loginStatus = 0, flag = 0;
char passwords[129][15];
char ids[129][15];

for(i = 1; i <= 129; i++) {
    sprintf(passwords[i-1], "BT21CSE%03d", i);//BT21CSE001-BT21CSE129
    sprintf(ids[i-1], "DSPD@E%03d", i);  //FORMAT-DSPD@Elast three digits of username
    
}
char Epasswords[15][15];
char Eids[15][15];

for(i = 1; i <=15; i++) {
    sprintf(Epasswords[i-1], "FVNITCSE%03d", i);//FVNITCSE001-FVNITCSE015
    sprintf(Eids[i-1], "E%03d", i); //Elast three digits of EUsername
    
}

char Username[10], password[15],confirm[15];
char EUsername[10], Epassword[15];
printf("\n Welcome To Assignment Management System\n");
printf(" Login as Student or Teacher?\n");
printf(" If teacher enter T, Else S : ");
scanf("%s",confirm);
if(strcmp(confirm,"S")==0)
{
	printf("\n");
printf(" Log in with Username and password!\n");
printf("\n Enter Your Username: ");
scanf("%s", Username);
printf("\nEnter Your Password: ");
scanf("%s", password);

for(i = 0; i < 129; i++) {
    if(strcmp(Username,passwords[i]) == 0 && strcmp(password, ids[i]) == 0) {
        loginStatus = 1;
        break;
    }
}
}
else if(strcmp(confirm,"T")==0)
{
	printf("Log in with Employeeid and password!\n");
	printf("\nEnter Your Employee ID:\n ");
    scanf("%s", EUsername);
    printf("\nEnter Your Password: ");
    scanf("%s", Epassword);

for(i = 0; i < 15; i++) {
    if(strcmp(EUsername, Epasswords[i]) == 0 && strcmp(Epassword, Eids[i]) == 0) {
        loginStatus = 1;
        break;
    }
}
}
 
if(loginStatus) {
    printf("Login successful!\n");
} else {
    printf("Invalid University ID or password! Please try again.\n");
}



    while(loginStatus == 1) {
        printf("\nLogin Successful\n");
        printf("1. Insert a student record\n");
        printf("2. Insert assignment record\n");
        printf("3. Change status of assignment and student lists\n");
        printf("4. Print the list of assignments that are declared but not evaluated\n");
        printf("5. Print the list student groups who have not submitted the assignments even if the due date is over\n");
        printf("6. Print the list of student groups for whom the assignment is yet-to-be-evaluated even though they have been submitted\n");
        printf("7. Print the details of student-groups for a given assignment id\n");
        printf("8. Print student groups receiving top marks in each of the assignment given\n");
         printf("9. Range-search – Search and print the details of assignments having assignment-id between assignment-id-1 and assignment-id-2.\n");
        printf("10. Logout\n");

        int option;
        printf("\nEnter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                insertStudentRecord();
                printf("AFTER ADDING NEW NODE \n");
                Ainorder(Aroot);
                break;

            case 2:
                 insertAssignRecord();
                printf("AFTER SECOND QUESTION \n");
               Sinorder(sroot);
              Ainorder(Aroot);
                break;

            case 3:
                submittingAssignments(sroot);
                evaluating_assignments(sroot);
                change_assign_status(Aroot);
                Sinorder(sroot);
              Ainorder(Aroot);
                break;
            case 4:
               changeassignments(Aroot);
               Sinorder(sroot);
              Ainorder(Aroot);
                break;
            case 5:
                printDueStudentgroups(sroot);
                Sinorder(sroot);
              Ainorder(Aroot);
                break;
            case 6:
                printEvalStudentGroups(sroot);
                break;
            case 7:
               Assigntraverse(Aroot);
                break;
            case 8:
                corresAssign(Aroot);
                break;
            case 9:
               rangesearch(Aroot,1,4);
                break;
            case 10:
                printf("Successfully logged out\n");
                loginStatus = 0;
                break;
            default:
                printf("\n  Invalid input. Please enter a number between 1 and 9.\n");
        }
    }
     
     if(flag==1)
     {
        printf("Thank you for using the assignment manager!\n");
    }

    return 0;
}
