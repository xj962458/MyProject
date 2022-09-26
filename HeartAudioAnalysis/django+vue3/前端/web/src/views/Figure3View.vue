<template>
  <div>
    <div>
      <FileInfo></FileInfo>
    </div>
    <div>
      <FileFigure3></FileFigure3>
    </div>
    <div>
      <FileUpload></FileUpload>
    </div>
    <div><FileList></FileList></div>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";
import FileFigure3 from "@/components/FileFigure3.vue";
import FileInfo from "@/components/FileInfo.vue";
import FileUpload from "@/components/FileUpload.vue";
import FileList from "@/components/FileList.vue";

@Options({
  components: {
    FileInfo,
    FileUpload,
    FileFigure3,
    FileList,
  },
})
export default class HomeView extends Vue {}
</script>
