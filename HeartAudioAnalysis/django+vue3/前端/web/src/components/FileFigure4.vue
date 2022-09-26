<template>
  <el-row :gutter="5" class="demo-image__placeholder">
    <el-col :span="12" class="block">
      <el-tag size="large" color="red" effect="dark">降噪前</el-tag>
      <el-image style="width: 60%;height: 60%" :src="`data:image/png;base64,${store.state.currentData.p14}`"></el-image>
    </el-col>

    <el-col :span="12" class="block">
      <el-tag size="large" color="brown" effect="dark">降噪后</el-tag>
      <el-image style="width: 60%;height: 60%" :src="`data:image/png;base64,${store.state.currentData.p24}`"></el-image>
    </el-col>
  </el-row>
</template>

<script lang="ts" setup>
import {useStore} from 'vuex'
const store = useStore()
</script>

<style scoped>
.el-row {
  display: flex;
  flex-wrap: wrap;
}

.el-col {
  border-radius: 4px;
  height: 100%;
}

.bg-purple-dark {
  background: #99a9bf;
}

.bg-purple {
  background: #d3dce6;
}

.bg-purple-light {
  background: #e5e9f2;
}

.grid-content {
  border-radius: 4px;
  min-height: 36px;
}

.row-bg {
  padding: 10px 0;
  background-color: #f9fafc;
}

.el-tag {
  display: flex;
  justify-content: center;
}

.el-image {
  height: 100%;
  width: 100%;
}
</style>
