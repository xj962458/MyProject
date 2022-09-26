<template>
  <div class="la">
    <el-card>
      <div class="input">
        <div id="tip1">
          <b>请输入一段想分析的文本：</b>
          <el-check-tag checked @click="rand_text">随机示例</el-check-tag>
        </div>
        <el-input
          v-model="textarea"
          :rows="6"
          placeholder="Please input"
          type="textarea"
        />
        <el-row>
          <el-col :span="20"><p id="tip2">输入文字请保持在500字以内！</p></el-col>
          <el-col id="button" :span="4">
            <el-button
              bg
              plain
              size="large"
              style="letter-spacing: 1px; font-size: medium"
              text
              type="primary"
              @click="start"
              >开始分析
            </el-button>
          </el-col>
        </el-row>
      </div>
    </el-card>
    <el-divider />
    <div class="result">
      <p><b>分析结果：</b></p>
      <el-row>
        <el-col :span="18">
          <el-card>
            <el-button
              v-for="(val, key) in result"
              :key="val + key"
              class="word"
              type="primary"
              @click="get_info(key, val)"
              >{{ key }}
            </el-button>
          </el-card>
        </el-col>
        <el-col :span="6">
          <el-card>
            <div class="text"><b>词汇：</b>{{ info.word }}</div>
            <div class="text"><b>词性：</b>{{ info.class }}</div>
            <div class="text"><b>实体：</b>{{ info.entity }}</div>
          </el-card>
        </el-col>
      </el-row>
    </div>
  </div>
</template>

<script lang="ts" setup>
import { reactive, ref } from "vue";
import axios from "axios";

let textarea = ref(
  "那是亲情中的互相信任与彼此成就，也是代际间的价值认同与精神传承，是我们的国家迎来从站起来、富起来到强起来的伟大飞跃的接续奋斗。"
); // 要分析的文本

let result = ref({}); //包含分析结果的对象

// 用于显示分词具体信息
let info = reactive({
  word: "",
  class: "",
  entity: "",
});

// 获取随机文本
const rand_text = () => {
  axios.get("http://xjfyt.top:8000/la/random_text").then((response) => {
    textarea.value = response.data;
  });
};

// 发起请求，进行分析
const start = () => {
  axios
    .get("http://xjfyt.top:8000/la/analysis?text=" + textarea.value)
    .then((response) => {
      result.value = response.data;
    });
};

// 分词结果详细显示
const get_info = (key: string, val: string) => {
  info.entity = "";
  const e = ["人名", "地名", "机构名", "时间"];
  info.word = key;
  info.class = val;
  if (e.includes(val)) {
    info.entity = val;
  }
  console.log(result);
};

start();
</script>

<style scoped>
#tip1 {
  text-align: left;
  letter-spacing: 1px;
}

#tip2 {
  text-align: left;
  width: 100%;
  height: 100%;
  letter-spacing: 2px;
  margin-top: 2px;
  color: #8e99a7;
}

.el-row {
  margin-top: 3px;
  /*color: var(--el-color-primary);*/
}

#button {
  text-align: right;
  padding-right: 3px;
  letter-spacing: 1px;
}

p {
  text-align: left;
  letter-spacing: 2px;
}

.word {
  float: left;
  margin-top: 1%;
  margin-right: 0.05%;
  background-color: #ffffff;
  letter-spacing: 1px;
  color: #409eff;
}

.el-card {
  height: 100%;
}

.text {
  font-size: 14px;
  letter-spacing: 1px;
  text-align: left;
  margin: 1px;
  padding: 10px;
}
</style>
