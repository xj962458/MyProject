<template>
  <div>
    <div>
      <FileInfo></FileInfo>
    </div>
    <div>
      <FileFigure1></FileFigure1>
    </div>
    <div>
      <FileUpload></FileUpload>
    </div>
    <div><FileList></FileList></div>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";
import FileFigure1 from "@/components/FileFigure1.vue";
import FileInfo from "@/components/FileInfo.vue";
import FileUpload from "@/components/FileUpload.vue";
import FileList from "@/components/FileList.vue";

@Options({
  components: {
    FileInfo,
    FileUpload,
    FileFigure1,
    FileList,
  },
})
export default class HomeView extends Vue {}
</script>
