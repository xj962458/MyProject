<template>
  <el-table
    ref="singleTableRef"
    :data="store.state.allData"
    highlight-current-row
    style="width: 100%"
    lazy
    @current-change="handleCurrentChange"
    :show-header="false"
    fixed="center"
  >
    <el-table-column type="index"> </el-table-column>
    <el-table-column property="filename"> </el-table-column>
    <el-table-column property="sr"> </el-table-column>
     <el-table-column property="times"></el-table-column>
    <el-table-column property="illness"> </el-table-column>
    <el-table-column property="position"> </el-table-column>
  </el-table>
</template>

<script lang="ts" setup>
import { ref } from "vue";
import type { ElTable } from "element-plus";
import { useStore } from 'vuex'

const store = useStore()
store.dispatch('getAllData')
interface User {
  filename: string;
  sr: number;
  illness: string;
  position:string;
}

const currentRow = ref();
const singleTableRef = ref<InstanceType<typeof ElTable>>();
const handleCurrentChange = (val: User | undefined) => {
  currentRow.value = val;
  store.commit("getCurrentData",val.filename)
};

</script>
