#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");
	// declare a list_head object by using LIST_HEAD macro
    static LIST_HEAD(birthday_list);         
    struct birthday
    {
        int day;
        int month;
        int year;
        struct list_head list;
    };
    struct birthday *ptr, *next;
    struct birthday *Bob;
    struct birthday *Alice;
    struct birthday *youngseaz;

    Bob = kmalloc(sizeof(*Bob), GFP_KERNEL);
    Bob -> day = 1;
    Bob -> month = 1;
    Bob -> year = 1990;
	// initializes the list member in struct birthday
    INIT_LIST_HEAD(&Bob -> list);

    Alice = kmalloc(sizeof(*Alice), GFP_KERNEL);
    Alice -> day = 2;
    Alice -> month = 2;
    Alice -> year = 1991;
    INIT_LIST_HEAD(&Alice -> list);
    
    youngseaz = kmalloc(sizeof(*youngseaz), GFP_KERNEL);
    youngseaz -> day = 15;
    youngseaz -> month = 4;
    youngseaz -> year = 1997;
    INIT_LIST_HEAD(&youngseaz -> list);

	//add this instance to the end of the linked list using the list add tail() macro
    list_add_tail(&Bob -> list, &birthday_list);
    list_add_tail(&Alice -> list, &birthday_list);
    list_add_tail(&youngseaz -> list, &birthday_list);

    list_for_each_entry(ptr, &birthday_list, list)
    {

        printk(KERN_INFO "%d/%d/%d \n", ptr -> month, ptr -> day,  ptr -> year);
    }
    
    //removing all elements from a linked list is 
    list_for_each_entry_safe(ptr, next, &birthday_list, list)
    {
	/* Removing elements from the list involves using the list_del() macro,
	which is passed a pointer to struct list head */
        list_del(&ptr->list);
        kfree(ptr);
    }

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) 
{
    printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
