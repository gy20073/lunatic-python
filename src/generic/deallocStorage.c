// This file will be included by THGenerateAllTypes
#define torch_Tensor TH_CONCAT_STRING_3(torch.,Real,Tensor)
#define torch_Storage TH_CONCAT_STRING_3(torch.,Real,Storage)

{
    THStorage* storage = luaT_toudata(LuaState, -1, torch_Storage);
    if (storage) {
      THStorage_(setFlag)(storage, TH_STORAGE_RESIZABLE);
      //printf("Releasing the underlying storage\n");
    }
}

#undef torch_Tensor
#undef torch_Storage
