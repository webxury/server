#include "item_windowfunc.h" 
#include "my_dbug.h"
#include "my_global.h"
#include "sql_select.h" // test if group changed

bool
Item_window_func::fix_fields(THD *thd, Item **ref)
{
  DBUG_ASSERT(fixed == 0);
  
  if (window_func->fix_fields(thd, ref))
    return TRUE;

  for (ORDER * curr = window_spec->partition_list.first; curr; curr=curr->next) {
    curr->item_ptr->fix_fields(thd, curr->item);
    Cached_item *tmp= new_Cached_item(thd, curr->item_ptr, TRUE);
    partition_fields.push_back(tmp);
  }

  fixed= 1;
  return FALSE;
}

void Item_window_func::advance_window() {

  int changed = test_if_group_changed(partition_fields);

  if (changed > -1) {
    window_func->clear();
  }
  window_func->add();
}
