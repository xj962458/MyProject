<template>
  <div>
    <el-row>
      <el-button id="add" type="primary" icon="el-icon-plus" @click="dialogFormVisible = true" size="large">
        <el-icon>
          <plus/>
        </el-icon>
      </el-button>
    </el-row>
    <el-dialog v-model="dialogFormVisible" title="上传音频文件">
      <el-form>
        <el-form-item label="文件名称" :label-width="formLabelWidth">
          <el-input v-model="filename" autocomplete="off"/>
          <el-upload ref="uploadRef" class="upload-demo" action="http://localhost:8000/heart/upload/"
                     :auto-upload="false" accept=".wav,.ogg,.mp3" :show-file-list="false" :on-change="handleChange"
                     :on-success="uploadSuccess" :on-error="uploadFail">
            <template #trigger>
              <el-button size="large" type="primary" class="ml-3" style="margin-right: 10px; margin-top: 5px">选择文件
                <el-icon>
                  <document-add/>
                </el-icon>
              </el-button>
            </template>

            <el-button size="large" class="ml-3" style="" type="success" @click="submitUpload">
              点击上传
              <el-icon>
                <upload-filled/>
              </el-icon>
            </el-button>
            <template #tip>
              <div class="el-upload__tip" v-show="msg">
                {{ msg }}
              </div>
            </template>

          </el-upload>
        </el-form-item>
      </el-form>
      <template #footer>
        <span class="dialog-footer">
          <el-button size="large" @click="cancel">取消</el-button>
          <el-button size="large" type="primary" @click="confirm">确认</el-button>
        </span>
      </template>
    </el-dialog>
  </div>
</template>

<script setup lang="ts">
import {ref} from "vue";
import {useStore} from 'vuex'
import {DocumentAdd, Plus, UploadFilled} from "@element-plus/icons-vue";
import type {UploadInstance} from "element-plus";

const uploadRef = ref<UploadInstance>();
const store = useStore()

const submitUpload = () => {
  uploadRef.value?.submit();
};

const dialogFormVisible = ref(false);
const formLabelWidth = "140px";
let filename = ref("")
let msg = ref("");
const handleChange = (file) => {
  filename.value = file.name;
}
const uploadSuccess = (response) => {
  msg.value = response.msg;
}

const uploadFail = (err) => {
  msg.value = err.msg;
}

const cancel = () => {
  dialogFormVisible.value = false
  msg.value = "";
  filename.value = "";
}
const confirm = () => {
  store.commit("getCurrentData", filename.value)
  dialogFormVisible.value = false
  msg.value = "";
  filename.value = "";
  store.dispatch("getAllData");
}
</script>

<style scoped>
.dialog-footer button:first-child {
  margin-right: 10px;
}

#add {
  font-family: "Microsoft YaHei UI", serif;
  font-weight: normal;
  font-size: 15px;
  width: 100%;
  text-align: center;
}
</style>
